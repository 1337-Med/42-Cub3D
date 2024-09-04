/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:19:40 by amejdoub          #+#    #+#             */
/*   Updated: 2024/09/04 19:31:36 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_trgb(unsigned char t, unsigned char r, unsigned char g,
		unsigned char b)
{
	return (*(int *)(unsigned char[4]){b, g, r, t});
}

float	distance_two_p(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

float	norm_angle(float angle)
{
	angle = fmod(angle, (2 * PI));
	if (angle < 0)
	{
		angle = (PI * 2) + angle;
	}
	return (angle);
}

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
	for (int i = 0; i < steps; i++) // Loop includes the endpoint
	{
		x += x_inc;
		y += y_inc;
		if (y < HEIGHT && y > 0 && x < WIDTH && x > 0)
			mlx_put_pixel(image, round(x), round(y), 0xFFFFFFFF);
	}
}

void	render_rec(int y, int x, mlx_image_t *image, char c)
{
	int		start_y;
	int		start_x;
	int		color;
	float	i;
	float	j;
	color = 0x0000000;
	start_y = y * 32 * MINI_FACTOR;
	start_x = x * 32 * MINI_FACTOR;
	if (c == 'W')
	{
		color = 0xFF0000FF;
	}
	else if (c == 'F')
	{
		color = 0x02f7b2;
	}
	i = 0;
	j = 0;
	while (i < 32 * MINI_FACTOR)
	{
		j = 0;
		while (j < 32 * MINI_FACTOR)
		{
			mlx_put_pixel(image, start_x + j, start_y + i, color);
			j++;
		}
		i++;
	}
}

void	render_rays(t_shared_data *data)
{
	int	i;

	i = 0;
	while (i < NUM_RAYS)
	{
		DDA(data->real_pos.x * MINI_FACTOR, data->real_pos.y * MINI_FACTOR,
			data->rays[i].ray_p.x * MINI_FACTOR, data->rays[i].ray_p.y
			* MINI_FACTOR, data->image);
		i++;
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
		{
			printf("test"), exit (0);
		}
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

bool steps_from_wall(t_shared_data *data, t_p_pos pos)
{
	float move_step;
	int i;
	t_p_pos	real;
	t_p_pos new;

	i = 0;
	real = data->real_pos;
		while (i < 2)
		{
			move_step = (float)data->player.walk_dir * data->player.move_speed;
			new.x = (float)real.x + cos((data->player.rota_angle))
				* (float)move_step;
			new.y = (float)real.y + sin((data->player.rota_angle))
				* (float)move_step;
			pos.x = (int)floor(new.x / 32.0);
			pos.y = (int)floor(new.y / 32.0);
			if (data->game_env->map[(int)pos.y][(int)pos.x] == '1')
			{
				return (false);
			}
			real.x = new.x;
			real.y = new.y;
			i++;
		}
		return (true);
}

bool	move_up_condition(t_shared_data *data)
{
	t_p_pos pos;
	int index;

	pos.x = 0;
	if (data->rays[WIDTH - 1].distance < data->rays[0].distance)
		index = WIDTH - 1;
	else
		index = 0;
	if ((data->player.walk_dir == 1 && data->rays && data->rays[index].distance > 12))
		return (true);
	else if (data->player.walk_dir == 1)
		return (false);
	else
	{
		return steps_from_wall(data, pos);
	}
	return (false);
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
        ((t_shared_data *)data)->player.rota_angle += norm_angle(delta_x * (0.5 * (PI / 180))); 
        rander_map(data);
    }
    last_x = current_x;
    mlx_set_mouse_pos(((t_shared_data *)data)->mlx, screen_center_x, screen_center_y);
    last_x = screen_center_x;
    rander_map(data);
	if (i < 2)
		i++;
}

int	raycaster(t_game_env *game_env)
{
	t_shared_data	data;
	t_player		player;

	data.rays = NULL;
	data.game_env = game_env;
	data.p_pos = get_player_pos(data.game_env->map);
	data.real_pos = get_player_pos(data.game_env->map);
	data.real_pos.x = (data.real_pos.x * 32) + 16;
	data.real_pos.y = (data.real_pos.y * 32) + 16;
	player.pos = data.real_pos;
	player.raduis = 3;
	player.walk_dir = 0;
	player.turn_dir = 0;
	player.rota_angle = PI / 2;
	player.move_speed = 8;
	player.rotate_speed = 4 * (PI / 180);
	data.player = player;
	data.mlx = NULL;
	data.image = NULL;
	if (!(data.mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", false)))
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (!(data.image = mlx_new_image(data.mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(data.mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (mlx_image_to_window(data.mlx, data.image, 0, 0) == -1)
	{
		mlx_close_window(data.mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
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
