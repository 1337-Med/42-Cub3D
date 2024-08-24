/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:19:40 by amejdoub          #+#    #+#             */
/*   Updated: 2024/08/24 19:31:07 by nbenyahy         ###   ########.fr       */
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

void	create_rays(t_shared_data *data)
{
	int		i;
	int		column_id;
	float	ray_angle;

	i = 0;
	column_id = 0;
	ray_angle = (norm_angle(data->player.rota_angle)) - (FOV / 2);
	data->rays = NULL;
	data->rays = ft_alloc(sizeof(t_rays) * (NUM_RAYS + 1), data->rays, CALLOC);
	while (i < NUM_RAYS)
	{
		data->rays[i].angle = norm_angle(ray_angle);
		// printf("%f angle \n", data->rays[i].angle);
		data->rays[i].wall_hit_x = 0;
		data->rays[i].wall_hit_y = 0;
		data->rays[i].ray_p.x = 0;
		data->rays[i].ray_p.y = 0;
		data->rays[i].horiz_x = -1;
		data->rays[i].horiz_y = -1;
		data->rays[i].vert_x = -1;
		data->rays[i].vert_y = -1;
		data->rays[i].distance = 0;
		data->rays[i].columnd_id = column_id;
		if (data->rays[i].angle >= 0 && data->rays[i].angle <= PI)
			data->rays[i].ray_down = true;
		else
			data->rays[i].ray_down = false;
		data->rays[i].ray_up = !data->rays[i].ray_down;
		if (data->rays[i].angle <= PI * 0.5 || data->rays[i].angle >= 1.5 * PI)
			data->rays[i].ray_right = true;
		else
			data->rays[i].ray_right = false;
		data->rays[i].ray_left = !data->rays[i].ray_right;
		i++;
		ray_angle += (float)(FOV / NUM_RAYS);
		column_id++;
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
void	get_vertical_inter(t_shared_data *data, int i)
{
	float	inter_x;
	float	inter_y;
	float	step_x;
	float	step_y;
	float	touch_x;
	int		map_y;
	int		map_x;

	inter_x = floor(data->real_pos.x / 32) * 32;
	if (data->rays[i].ray_right)
		inter_x += 32;
	inter_y = data->real_pos.y + ((inter_x - data->real_pos.x)
			* tan(data->rays[i].angle));
	step_x = 32;
	if (data->rays[i].ray_left)
		step_x = -step_x;
	step_y = 32 * tan(data->rays[i].angle);
	if (data->rays[i].ray_up && step_y > 0)
		step_y = -step_y;
	if (data->rays[i].ray_down && step_y < 0)
		step_y = -step_y;
	// while (inter_y > 0 && inter_x > 0 && inter_y < HEIGHT && inter_x < WIDTH)
	while (inter_y > 0 && inter_x > 0)
	{
		touch_x = inter_x;
		if (data->rays[i].ray_left)
			touch_x--;
		map_y = (int)floor((inter_y / 32));
		map_x = (int)floor((touch_x / 32));
		if (map_y < 0 || map_y >= (int)ft_arrsize(data->game_env->map)
			|| map_x < 0 || map_x >= (int)ft_strlen(data->game_env->map[map_y]))
		{
			inter_y += step_y;
			inter_x += step_x;
			data->rays[i].vert_x = -1;
			data->rays[i].vert_y = -1;
			// printf ("womp womp\n");
			return ;
		}
		else if (data->game_env->map[map_y])
		{
			if (data->game_env->map[map_y][map_x] == '1')
			{
				// printf("here 1\n");
				data->rays[i].vert_x = inter_x;
				data->rays[i].vert_y = inter_y;
				return ;
			}
		}
		inter_y += step_y;
		inter_x += step_x;
		// printf("%d %f %f %d %d %c \n", i, inter_x, inter_y,
			// (int)floor((inter_x / 32)), (int)floor((inter_y / 32)),
			// data->game_env->map[5][29]);
	}
	// printf("here 2\n");
}

void	get_horizontal_inter(t_shared_data *data, int i)
{
	float	inter_x;
	float	inter_y;
	float	step_x;
	float	step_y;
	float	touch_y;
	int		map_y;
	int		map_x;

	inter_y = floor(data->real_pos.y / 32) * 32;
	inter_y += data->rays[i].ray_down ? 32 : 0;
	inter_x = data->real_pos.x + ((inter_y - data->real_pos.y)
			/ tan(data->rays[i].angle));
	step_y = 32;
	if (data->rays[i].ray_up)
		step_y = -step_y;
	step_x = 32 / tan(data->rays[i].angle);
	if ((data->rays[i].ray_left && step_x > 0) || (data->rays[i].ray_right
			&& step_x < 0))
		step_x = -step_x;
	// while (inter_y > 0 && inter_x > 0 && inter_y < HEIGHT && inter_x < WIDTH
		// && data->game_env->map[(int)inter_y / 32])
	while (inter_y > 0 && inter_x > 0 && inter_y < HEIGHT)
	{
		touch_y = inter_y;
		if (data->rays[i].ray_up)
			touch_y--;
		map_y = floor(touch_y / 32);
		map_x = floor(inter_x / 32);
		if (map_y < 0 || map_y >= (int)ft_arrsize(data->game_env->map)
			|| map_x < 0 || map_x > (int)ft_strlen(data->game_env->map[map_y]))
		{
			inter_y += step_y;
			inter_x += step_x;
			data->rays[i].horiz_x = -1;
			data->rays[i].horiz_y = -1;
			return ;
		}
		if (data->game_env->map[map_y])
		{
			if (data->game_env->map[map_y][map_x] == '1')
			{
				data->rays[i].horiz_x = inter_x;
				data->rays[i].horiz_y = inter_y;
				return ;
			}
		}
		inter_y += step_y;
		inter_x += step_x;
	}
}

void	cast_rays(t_shared_data *data, int num_rays)
{
	int		i;
	float	horz;
	float	vertical;

	i = 0;
	while (i < num_rays)
	{
		get_horizontal_inter(data, i);
		horz = distance_two_p(data->real_pos.x, data->real_pos.y,
				data->rays[i].horiz_x, data->rays[i].horiz_y);
		get_vertical_inter(data, i);
		vertical = distance_two_p(data->real_pos.x, data->real_pos.y,
				data->rays[i].vert_x, data->rays[i].vert_y);
		if ((int)data->rays[i].horiz_x == -1)
		{
			data->rays[i].distance = vertical;
			data->rays[i].distance = data->rays[i].distance
				* cos(data->rays[i].angle - data->player.rota_angle);
			data->rays[i].ray_p.x = data->rays[i].vert_x;
			data->rays[i].ray_p.y = data->rays[i].vert_y;
			data->rays[i].ray_down = 0;
			data->rays[i].ray_up = 0;
		}
		else if ((int)data->rays[i].vert_x == -1)
		{
			data->rays[i].distance = horz;
			data->rays[i].distance = data->rays[i].distance
				* cos(data->rays[i].angle - data->player.rota_angle);
			data->rays[i].ray_p.x = data->rays[i].horiz_x;
			data->rays[i].ray_p.y = data->rays[i].horiz_y;
			data->rays[i].ray_left = 0;
			data->rays[i].ray_right = 0;
		}
		else if ((int)data->rays[i].horiz_x != -1
			&& (int)data->rays[i].vert_x != -1)
		{
			if (horz <= vertical)
			{
				data->rays[i].distance = horz;
				data->rays[i].distance = data->rays[i].distance
					* cos(data->rays[i].angle - data->player.rota_angle);
				data->rays[i].ray_p.x = data->rays[i].horiz_x;
				data->rays[i].ray_p.y = data->rays[i].horiz_y;
				data->rays[i].ray_left = 0;
				data->rays[i].ray_right = 0;
			}
			else
			{
				data->rays[i].distance = vertical;
				data->rays[i].distance = data->rays[i].distance
					* cos(data->rays[i].angle - data->player.rota_angle);
				data->rays[i].ray_p.x = data->rays[i].vert_x;
				data->rays[i].ray_p.y = data->rays[i].vert_y;
				data->rays[i].ray_down = 0;
				data->rays[i].ray_up = 0;
			}
		}
		i++;
	}
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
		if (data->rays[i].distance < 0.5)
			data->rays[i].distance = 0.5;
		distancepp = (WIDTH / 2) / tan(FOV / 2);
		wall_height = (32 / data->rays[i].distance) * distancepp;
		wall_top = (HEIGHT / 2) - (wall_height / 2);
		wall_bottom = (HEIGHT / 2) + (wall_height / 2);
		rander_textures(data, i, wall_top, wall_bottom);
		i++;
	}
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
				render_rec(y, x, data->image, 'F');
			x++;
		}
		y++;
	}
	render_rays(data);
	// move_down_condition(data);
}
bool	move_down_condition(t_shared_data *data)
{
	float			opposite;
	float			ray_angle;
	t_shared_data	back_data;

	opposite = fmod(data->player.rota_angle + degree_to_raidian(180),
			degree_to_raidian(360));
	ray_angle = ((data->player.rota_angle + opposite)) / 2;
	// printf ("ray angle %f\n", ray_angle);
	back_data.game_env = data->game_env;
	back_data.player = data->player;
	back_data.player.rota_angle = opposite;
	back_data.rays = NULL;
	back_data.rays = ft_alloc(sizeof(t_rays) * (1), back_data.rays, CALLOC);
	back_data.rays[0].angle = norm_angle(ray_angle);
	back_data.rays[0].wall_hit_x = 0;
	back_data.rays[0].wall_hit_y = 0;
	back_data.rays[0].ray_p.x = 0;
	back_data.rays[0].ray_p.y = 0;
	back_data.rays[0].horiz_x = -1;
	back_data.rays[0].horiz_y = -1;
	back_data.rays[0].vert_x = -1;
	back_data.rays[0].vert_y = -1;
	back_data.rays[0].distance = 0;
	if (back_data.rays[0].angle >= 0 && back_data.rays[0].angle <= PI)
		back_data.rays[0].ray_down = true;
	else
		back_data.rays[0].ray_down = false;
	back_data.rays[0].ray_up = !back_data.rays[0].ray_down;
	if (back_data.rays[0].angle <= PI * 0.5 || back_data.rays[0].angle >= 1.5
		* PI)
		back_data.rays[0].ray_right = true;
	else
		back_data.rays[0].ray_right = false;
	back_data.rays[0].ray_left = !back_data.rays[0].ray_right;
	cast_rays(&back_data, 1);
	// printf("distance %f\b", back_data.rays[0].distance);
	DDA(data->real_pos.x * MINI_FACTOR, data->real_pos.y * MINI_FACTOR,
		back_data.rays[0].ray_p.x * MINI_FACTOR, back_data.rays[0].ray_p.y
		* MINI_FACTOR, data->image);
	return (true);
}
bool	move_up_condition(t_shared_data *data)
{
	int		i;
		t_p_pos new;
		float move_step;
		t_p_pos pos;
	t_p_pos	real;

	// printf("here\n");
	// if(move_down_condition(data))
	// 	return (true);
	if ((data->player.walk_dir == 1 && data->rays && data->rays[WIDTH
			/ 2].distance > 9))
		return (true);
	if (data->player.walk_dir == -1)
	{
		i = 0;
		real = data->real_pos;
		while (i < 2)
		{
				// printf("hehe\n");
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
	return (false);
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
	data->player.rota_angle += norm_angle((float)data->player.turn_dir
			* data->player.rotate_speed);
	// data->player.rota_angle = norm_angle(data->player.rota_angle);
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
		&& data->game_env->map[r_y][r_x] != '1' && move_up_condition(data))
	{
		data->real_pos.x = new_x;
		data->real_pos.y = new_y;
	}
	rander_map(data);
}
void ft_loop(void *data)
{
    static int last_x = 0;
    int current_x, current_y;
	mlx_set_cursor_mode(((t_shared_data *)data)->mlx, MLX_MOUSE_HIDDEN);
    mlx_get_mouse_pos(((t_shared_data *)data)->mlx, &current_x, &current_y);
    int delta_x = current_x - last_x;
    if (delta_x != 0)
    {
        ((t_shared_data *)data)->player.rota_angle += norm_angle(delta_x * (0.5 * (PI / 180))); 
        rander_map(data);
    }
    last_x = current_x;
    int screen_center_x = WIDTH / 2;
    int screen_center_y = HEIGHT / 2;
    mlx_set_mouse_pos(((t_shared_data *)data)->mlx, screen_center_x, screen_center_y);
    last_x = screen_center_x;
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
	player.rotate_speed = 5 * (PI / 180);
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
	// create_rays(&data);
	texture_to_img(&data);
	rander_map(&data);
	mlx_key_hook(data.mlx, ft_hook, &data);
	mlx_loop_hook(data.mlx, ft_loop, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
	return (0);
}
