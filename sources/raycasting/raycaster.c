/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:19:40 by amejdoub          #+#    #+#             */
/*   Updated: 2024/08/15 16:40:56 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}


void	DDA(int x1, int y1, int x2, int y2, mlx_image_t *image)
{
	int		dx;
	int		dy;
	int		steps;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;

	dx = x2 - x1;
	dy = y2 - y1;
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	x_inc = dx / (float)steps;
	y_inc = dy / (float)steps;
	x = x1;
	y = y1;
	mlx_put_pixel(image, round(x), round(y), 0xFFFFFFFF);
	for (int i = 0; i < steps; i++)
	{
		x += x_inc;
		y += y_inc;
		mlx_put_pixel(image, round(x), round(y), 0xFFFFFFFF);
	}
}
void	render_rec(int y, int x, mlx_image_t *image, char c)
{
	int	start_y;
	int	start_x;
	int	color;
	int	i;
	int	j;

	start_y = y * 32;
	start_x = x * 32;
	if (c == 'W')
		color = 0xFF0000FF;
	else if (c == 'F')
		color = 0x02f7b2;
	i = 0;
	j = 0;
	while (i < 32)
	{
		j = 0;
		while (j < 32)
		{
			mlx_put_pixel(image, start_x + j, start_y + i, color);
			j++;
		}
		i++;
	}
}

void  create_rays(t_shared_data *data)
{
	int i = 0;
	int column_id = 0;
    float ray_angle = data->player.rota_angle - (FOV / 2);
	data->rays = ft_alloc(sizeof(t_rays) * (NUM_RAYS + 1), data->rays, CALLOC);
	while (i < NUM_RAYS)
	{
		data->rays[i].angle = ray_angle;
		data->rays[i].columnd_id = column_id;
		i++;
		ray_angle += FOV / NUM_RAYS;
		column_id++;
	}
}

void cast_rays(t_shared_data *data)
{
    int i = 0;
    while (i < NUM_RAYS)
    {
        DDA(data->real_pos.x, data->real_pos.y, data->real_pos.x + cos(data->rays[i].angle) * 32, data->real_pos.y + sin(data->rays[i].angle) * 32, data->image);
        i++;
    }
}
void	render_player(t_shared_data *data)
{
	int	color;
	int	i;
	int	j;

	color = 0xFFFFFFFF;
	i = -5;
	j = -5;
	while (i <= 5)
	{
		j = -5;
		while (j <= 5)
		{
			mlx_put_pixel(data->image, data->real_pos.x + j, data->real_pos.y
				+ i, color);
			j++;
		}
		i++;
	}
	create_rays(data);
    cast_rays(data);
	DDA(data->real_pos.x, data->real_pos.y, data->real_pos.x
		+ cos((data->player.rota_angle)) * 32, data->real_pos.y
		+ sin((data->player.rota_angle)) * 32, data->image);
}

void	rander_map(t_shared_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (data->game_env->map[y])
	{
		x = 0;
		while (data->game_env->map[y][x])
		{
			if (data->game_env->map[y][x] == '1')
				render_rec(y, x, data->image, 'W');
			if (data->game_env->map[y][x] == '0'
				|| data->game_env->map[y][x] == 'N')
			{
				render_rec(y, x, data->image, 'F');
			}
			x++;
		}
		y++;
	}
	render_player(data);
}

void	ft_hook(mlx_key_data_t key, void *param)
{
	t_shared_data	*data;
	float			move_step;
	int				r_x;
	int				r_y;
	int				test_x;
	int				test_y;

	float new_x, new_y;
	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (key.key == MLX_KEY_RIGHT && key.action == MLX_RELEASE)
	{
		data->player.turn_dir = 0;
	}
	if (key.key == MLX_KEY_LEFT && key.action == MLX_RELEASE)
	{
		data->player.turn_dir = 0;
	}
	if (key.key == MLX_KEY_RIGHT && mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->player.turn_dir = 1;
	}
	if (key.key == MLX_KEY_LEFT && mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->player.turn_dir = -1;
	}
	if (key.key == MLX_KEY_S && key.action == MLX_RELEASE)
	{
		data->player.walk_dir = 0;
	}
	if (key.key == MLX_KEY_W && key.action == MLX_RELEASE)
	{
		data->player.walk_dir = 0;
	}
	if (key.key == MLX_KEY_W && mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		data->player.walk_dir = 1;
	}
	if (key.key == MLX_KEY_S && mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		data->player.walk_dir = -1;
	}
	data->player.rota_angle += (float)data->player.turn_dir
		* data->player.rotate_speed;
	move_step = (float)data->player.walk_dir * data->player.move_speed;
	new_x = (float)data->real_pos.x + cos((data->player.rota_angle))
		* (float)move_step;
	new_y = (float)data->real_pos.y + sin((data->player.rota_angle))
		* (float)move_step;
	r_x = floor(new_x / 32.0);
	r_y = floor(new_y / 32.0);
	test_x = data->real_pos.x / 32;
	test_y = data->real_pos.y / 32;
	if ((data->game_env->map[r_y][test_x] != '1'
			|| data->game_env->map[test_y][r_x] != '1')
		&& data->game_env->map[r_y][r_x] != '1')
	{
		data->real_pos.x = new_x;
		data->real_pos.y = new_y;
	}
	rander_map(data);
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
	player.move_speed = 4;
	player.rotate_speed = 4 * (PI / 180);
	data.player = player;
	data.mlx = NULL;
	data.image = NULL;
	if (!(data.mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true)))
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
	rander_map(&data);
	mlx_key_hook(data.mlx, ft_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
	return (0);
}
