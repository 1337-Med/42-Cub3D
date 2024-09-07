/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:09:58 by amejdoub          #+#    #+#             */
/*   Updated: 2024/09/06 19:13:16 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool move_condition(t_shared_data *data, float angle, t_p_pos new, t_cord old)
{
	int i = 0;
    t_cord r;
    float			move_step;
	while (i < 2)
	{
		move_step = data->player.move_speed;
		new.x = data->real_pos.x + cos(angle) * move_step;
		new.y = data->real_pos.y + sin(angle) * move_step;
		r.x = floor(new.x / 32.0);
		r.y = floor(new.y / 32.0);
		old.x = data->real_pos.x / 32;
		old.y = data->real_pos.y / 32;
		if ((data->game_env->map[r.y][old.x] != '1'
			|| data->game_env->map[old.y][r.x] != '1')
			&& data->game_env->map[r.y][r.x] != '1')
		{
			data->real_pos.x = new.x;
			data->real_pos.y = new.y;
		}
		else
			return false;
		i++;
	}
	return true;
}

void movement_a(t_shared_data *data)
{
    t_p_pos new;
    t_cord r;
    float			move_step;
    t_cord old;

    move_step = data->player.move_speed;
		float left_angle = data->player.rota_angle - PI / 2; 

		new.x = data->real_pos.x + cos(left_angle) * move_step;
		new.y = data->real_pos.y + sin(left_angle) * move_step;

			r.x = floor(new.x / 32.0);
			r.y = floor(new.y / 32.0);
			old.x = data->real_pos.x / 32;
			old.y = data->real_pos.y / 32;

		if ((data->game_env->map[r.y][old.x] != '1'
			|| data->game_env->map[old.y][r.x] != '1')
			&& data->game_env->map[r.y][r.x] != '1' && move_condition(data, left_angle, new, old))
		{
			data->real_pos.x = new.x;
			data->real_pos.y = new.y;
		}
		rander_map(data);
}

void movement_d(t_shared_data *data)
{
    t_p_pos new;
    t_cord r;
    float			move_step;
    t_cord old;

    move_step = data->player.move_speed;
		float right_angle = data->player.rota_angle + PI / 2; 

		new.x = data->real_pos.x + cos(right_angle) * move_step;
		new.y = data->real_pos.y + sin(right_angle) * move_step;

			r.x = floor(new.x / 32.0);
			r.y = floor(new.y / 32.0);
			old.x = data->real_pos.x / 32;
			old.y = data->real_pos.y / 32;

		if ((data->game_env->map[r.y][old.x] != '1'
			|| data->game_env->map[old.y][r.x] != '1')
			&& data->game_env->map[r.y][r.x] != '1' && move_condition(data, right_angle, new, old))
		{
			data->real_pos.x = new.x;
			data->real_pos.y = new.y;
		}
		rander_map(data);
}

void walkturn_dir(t_shared_data *data, mlx_key_data_t key)
{
	if (key.key == MLX_KEY_RIGHT && key.action == MLX_RELEASE)
		data->player.turn_dir = 0;
	if (key.key == MLX_KEY_LEFT && key.action == MLX_RELEASE)
		data->player.turn_dir = 0;
	if (key.key == MLX_KEY_RIGHT && mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player.turn_dir = 1;
	if (key.key == MLX_KEY_LEFT && mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player.turn_dir = -1;
	if (key.key == MLX_KEY_S && key.action == MLX_RELEASE)
		data->player.walk_dir = 0;
	if (key.key == MLX_KEY_W && key.action == MLX_RELEASE)
		data->player.walk_dir = 0;
	if (key.key == MLX_KEY_W && mlx_is_key_down(data->mlx, MLX_KEY_W))
		data->player.walk_dir = 1;
	if (key.key == MLX_KEY_S && mlx_is_key_down(data->mlx, MLX_KEY_S))
		data->player.walk_dir = -1;
}

void calcul_new_cord(t_shared_data *data)
{
	float move_step;
	t_p_pos new;
	t_cord r;
	t_cord old;
	data->player.rota_angle += (float)data->player.turn_dir
			* data->player.rotate_speed;
	data->player.rota_angle = norm_angle(data->player.rota_angle);
	move_step = (float)data->player.walk_dir * data->player.move_speed;
	new.x = (float)data->real_pos.x + cos((data->player.rota_angle))
		* (float)move_step;
	new.y = (float)data->real_pos.y + sin((data->player.rota_angle))
		* (float)move_step;
	r.x = floor(new.x / 32.0);
	r.y = floor(new.y / 32.0);
	old.x = data->real_pos.x / 32;
	old.y = data->real_pos.y / 32;
	if ((data->game_env->map[r.y][old.x] != '1'
			|| data->game_env->map[old.y][r.x] != '1')
		&& data->game_env->map[r.y][r.x] != '1' && move_up_condition(data))
	{
		data->real_pos.x = new.x;
		data->real_pos.y = new.y;
	}
}

void	ft_hook(mlx_key_data_t key, void *param)
{
	t_shared_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (key.key == MLX_KEY_A && mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
        movement_a(data);
		return ;
	}
	if (key.key == MLX_KEY_D && mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
        movement_d(data);
		return ;
	}
	walkturn_dir(data, key);
	calcul_new_cord(data);
	rander_map(data);
}
