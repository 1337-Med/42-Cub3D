/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_condition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:28:51 by amejdoub          #+#    #+#             */
/*   Updated: 2024/09/22 12:25:38 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	steps_from_wall(t_shared_data *data, t_p_pos pos)
{
	float	move_step;
	int		i;
	t_p_pos	real;
	t_p_pos	new;
	float	angle;

	i = 0;
	real = data->real_pos;
	angle = data->player.rota_angle;
	while (i < 10)
	{
		move_step = (float)data->player.walk_dir * data->player.move_speed;
		new.x = (float)real.x + cos(angle) * (float)move_step;
		new.y = (float)real.y + sin(angle) * (float)move_step;
		pos.x = (int)floor(new.x / 32.0);
		pos.y = (int)floor(new.y / 32.0);
		if (data->game_env->map[(int)pos.y][(int )floor(real.x / 32)] == '1' || data->game_env->map[(int )floor(real.y / 32)][(int )pos.x] == '1' || data->game_env->map[(int)pos.y][(int)pos.x] == '1')
		{
			// data->player.rotate_speed = 12 * (PI / 180);
			
	// printf("FALSE\n");
			return (false);
		}
		real.x = new.x;
		real.y = new.y;
		i++;
	}
	// printf("TRUE\n");

	// data->player.rotate_speed =4 * (PI / 180);
	return (true);
}

bool	move_up_condition(t_shared_data *data)
{
	t_p_pos	pos;
	// int		index;

	pos.x = 0;
	// if (data->rays[NUM_RAYS - 1].distance < data->rays[0].distance)
	// 	index = (NUM_RAYS - 1) - ((NUM_RAYS / 2 ) / 2);
	// else
	// 	index = (NUM_RAYS / 2) / 2;	
	// if ( data->rays[index].distance > 10)
	// 	data->player.rotate_speed =4 * (PI / 180);
	// 	return (true);
	// else if (data->player.walk_dir == 1)
	// 	return (false);
	if (data->player.walk_dir != 0)
	{
		return (steps_from_wall(data, pos));
	}
	return (false);
}
