/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:19:40 by amejdoub          #+#    #+#             */
/*   Updated: 2024/09/07 15:33:52 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	DDA(float x1, float y1, float x2, float y2, mlx_image_t *image)
{
	float	dx;
	float	dy;
	float	steps;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;

	dx = x2 - x1;
	dy = y2 - y1;
	steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	x_inc = dx / (float)steps;
	y_inc = dy / (float)steps;
	x = x1;
	y = y1;
	mlx_put_pixel(image, round(x), round(y), 0xFFFFFFFF);
	for (int i = 0; i < steps; i++)
	{
		x += x_inc;
		y += y_inc;
		if (y < HEIGHT && y > 0 && x < WIDTH && x > 0)
			mlx_put_pixel(image, round(x), round(y), 0xFFFFFFFF);
	}
}

char **minimap_parse(t_shared_data *data)
{
	int p_x = (int )floor((data->real_pos.x) / 32);
	int p_y = (int )floor((data->real_pos.y) / 32);
	int start = p_y;
	int  end = p_y;
	int i = 0;
	while (i < 10)
	{
		if (!start)
			break ;
		start--;
		i++;
	}
	data->p_pos.y = (data->real_pos.y - (start * 32));
	int lim = 10;
	if (i != 10)
		lim += 10 - i;
	i = 0;
	while (i < lim)
	{
		if (end >= (int)ft_arrsize(data->game_env->map) || !data->game_env->map[end])
			break ;
		end++;
		i++;
	}
	char **mini_map = NULL;
	mini_map = ft_alloc(sizeof(char *) * (end - start + 1), mini_map, MALLOC);
	i = 0;
	int lim2 = -10;
	while (start + i < end)
	{
		lim = 20;
		lim2 = -10;
		int index = p_x + lim2;
		if (index < 0)
			index = 0;
		mini_map[i] = ft_substr(data->game_env->map[start + i], index, lim);
		if (i + start == p_y)
			data->p_pos.x = ((data->real_pos.x - (index * 32)));
		i++;
	}
	mini_map[i] = NULL;
	return (mini_map);
}

void	rander_map(t_shared_data *data)
{
	int		i;
	int		p;
	float	distancepp;
	float	wall_height;
	int		wall_top;
	int		wall_bottom;
	int		x;
	int		y;
	char **mini_map = NULL;

	create_rays(data);
	cast_rays(data, NUM_RAYS);
	i = 0;
	while (i < HEIGHT)
	{
		p = 0;
		while (p < WIDTH)
		{
			if (i < HEIGHT / 2)
				mlx_put_pixel(data->image, p, i, data->game_env->ceiling);
			else
				mlx_put_pixel(data->image, p, i, data->game_env->floor);
			p++;
		}
		i++;
	}
	i = 0;
	while (i < NUM_RAYS)
	{
		if (data->rays[i].distance == 0)
			data->rays[i].distance = 0.5;
		distancepp = (WIDTH / 2) / tan(FOV / 2);
		wall_height = (32 / data->rays[i].distance) * distancepp;
		wall_top = (HEIGHT / 2) - (wall_height / 2);
		wall_bottom = (HEIGHT / 2) + (wall_height / 2);
		rander_textures(data, i, wall_top, wall_bottom);
		i++;
	}
	mini_map = minimap_parse(data);
	x = 0;
	y = 0;
	while (y < 193)
	{
		x = 0;
		while (x < 257)
		{
			mlx_put_pixel(data->image, x, y, data->game_env->floor);
			x++;
		}
		y++;
	}
	y = 0;
	while (mini_map[y])
	{
		x = 0;
		while (mini_map[y][x])
		{
			if (mini_map[y][x] == '1')
				render_rec(y, x, data->image, 'W');
			if (mini_map[y][x] == '0'
				|| mini_map[y][x] == 'N')
				render_rec(y, x, data->image, 'F');
			x++;
		}
		y++;
	}
	mlx_put_pixel(data->image, data->p_pos.x * MINI_FACTOR, data->p_pos.y * MINI_FACTOR, 0xFFFFFFFF);
	DDA(data->p_pos.x * MINI_FACTOR, data->p_pos.y * MINI_FACTOR, data->p_pos.x * MINI_FACTOR + 50 * cos(data->player.rota_angle),
	data->p_pos.y * MINI_FACTOR + 50 * sin(data->player.rota_angle), data->image);
	i = 0;
	while (mini_map && mini_map[i])
		ft_alloc( 0, mini_map[i++], FREE_PTR);
	ft_alloc(0,mini_map, FREE_PTR);
}

void ft_loop(void *data)
{
    static int last_x = WIDTH / 2;
	static int i = 0;
    int current_x = WIDTH / 2, current_y = HEIGHT / 2;
    int screen_center_x = WIDTH / 2;
    int screen_center_y = HEIGHT / 2;

	if (i > 1)
    	mlx_get_mouse_pos(((t_shared_data *)data)->mlx, &current_x, &current_y);
    int delta_x = current_x - last_x;
    if (delta_x != 0)
    {
        ((t_shared_data *)data)->player.rota_angle += delta_x * 0.01;
		((t_shared_data *)data)->player.rota_angle = norm_angle(((t_shared_data *)data)->player.rota_angle);
    }
    last_x = current_x;
    mlx_set_mouse_pos(((t_shared_data *)data)->mlx, screen_center_x, screen_center_y);
    last_x = screen_center_x;
    rander_map(data);
	if (i < 2)
		i++;
}

void init_raycaster(t_shared_data *data, t_game_env *game_env)
{
	data->rays = NULL;
	data->game_env = game_env;
	data->p_pos = get_player_pos(data->game_env->map);
	data->real_pos = get_player_pos(data->game_env->map);
	data->real_pos.x = (data->real_pos.x * 32) + 16;
	data->real_pos.y = (data->real_pos.y * 32) + 16;
	data->player.pos = data->real_pos;
	data->player.raduis = 3;
	data->player.walk_dir = 0;
	data->player.turn_dir = 0;
	data->player.rota_angle =  PI / 2;
	data->player.move_speed = 8;
	data->player.rotate_speed = 4 * (PI / 180);
	data->mlx = NULL;
	data->image = NULL;
}

void init_mlx(t_shared_data *data)
{
	if (!(data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", false)))
	{
		puts(mlx_strerror(mlx_errno));
		exit (EXIT_FAILURE);
	}
	if (!(data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		exit (EXIT_FAILURE);
	}
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		exit (EXIT_FAILURE);
	}
}

int	raycaster(t_game_env *game_env)
{
	t_shared_data	data;

	init_raycaster(&data, game_env);
	init_mlx(&data);
	create_rays(&data);
	texture_to_img(&data);
	rander_map(&data);
	mlx_set_cursor_mode(data.mlx, MLX_MOUSE_HIDDEN);
    mlx_set_mouse_pos(data.mlx, WIDTH / 2, HEIGHT / 2);
	mlx_key_hook(data.mlx, ft_hook, &data);
	mlx_loop_hook(data.mlx, ft_loop, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
