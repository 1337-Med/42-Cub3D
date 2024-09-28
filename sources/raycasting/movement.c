/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:09:58 by amejdoub          #+#    #+#             */
/*   Updated: 2024/09/28 11:13:19 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	move_condition(t_shared_data *data, float angle, t_p_pos new,
	t_cord old)
{
	int		i;
	t_cord	r;

	i = 0;
	new = data->real_pos;
	old.x = new.x / 32;
	old.y = new.y / 32;
	while (i < 5)
	{
		r.x = floor(new.x / 32.0);
		r.y = floor(new.y / 32.0);
		if ((data->game_env->map[r.y][old.x] != '1' \
				|| data->game_env->map[old.y][r.x] != '1')
			&& data->game_env->map[r.y][r.x] != '1')
		{
			old.x = new.x / 32;
			old.x = new.y / 32;
			new.x += cos(angle) * data->player.move_speed;
			new.y += sin(angle) * data->player.move_speed;
		}
		else
			return (false);
		i++;
	}
	return (true);
}

void	movement_a(t_shared_data *data)
{
	t_p_pos	new;
	t_cord	r;
	float	move_step;
	t_cord	old;
	float	left_angle;

	move_step = data->player.move_speed;
	left_angle = data->player.rota_angle - PI / 2;
	new.x = data->real_pos.x + cos(left_angle) * move_step;
	new.y = data->real_pos.y + sin(left_angle) * move_step;
	r.x = floor(new.x / 32.0);
	r.y = floor(new.y / 32.0);
	old.x = data->real_pos.x / 32;
	old.y = data->real_pos.y / 32;
	if ((data->game_env->map[r.y][old.x] != '1' \
			|| data->game_env->map[old.y][r.x] != '1') \
		&& data->game_env->map[r.y][r.x] != '1' && move_condition(data, \
			left_angle, new, old))
	{
		data->real_pos.x = new.x;
		data->real_pos.y = new.y;
	}
	render_map(data);
}

void	movement_d(t_shared_data *data)
{
	t_p_pos	new;
	t_cord	r;
	float	move_step;
	t_cord	old;
	float	right_angle;

	move_step = data->player.move_speed;
	right_angle = data->player.rota_angle + PI / 2;
	new.x = data->real_pos.x + cos(right_angle) * move_step;
	new.y = data->real_pos.y + sin(right_angle) * move_step;
	r.x = floor(new.x / 32.0);
	r.y = floor(new.y / 32.0);
	old.x = data->real_pos.x / 32;
	old.y = data->real_pos.y / 32;
	if ((data->game_env->map[r.y][old.x] != '1' \
			|| data->game_env->map[old.y][r.x] != '1') \
		&& data->game_env->map[r.y][r.x] != '1' && move_condition(data, \
			right_angle, new, old))
	{
		data->real_pos.x = new.x;
		data->real_pos.y = new.y;
	}
	render_map(data);
}

void	walkturn_dir(t_shared_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT) == false)
		data->player.turn_dir = 0;
	if (!mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player.turn_dir = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player.turn_dir = 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player.turn_dir = -1;
	if (!mlx_is_key_down(data->mlx, MLX_KEY_W))
		data->player.walk_dir = 0;
	if (!mlx_is_key_down(data->mlx, MLX_KEY_S))
		data->player.walk_dir = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		data->player.walk_dir = 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		data->player.walk_dir = -1;
}

void	calcul_new_cord(t_shared_data *data)
{
	float	move_step;
	t_p_pos	new;
	t_cord	r;
	t_cord	old;

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
	if ((data->game_env->map[r.y][old.x] != '1' \
			|| data->game_env->map[old.y][r.x] != '1') \
		&& data->game_env->map[r.y][r.x] != '1' && move_up_condition(data))
	{
		data->real_pos.x = new.x;
		data->real_pos.y = new.y;
	}
}
