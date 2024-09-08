/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_condition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:28:51 by amejdoub          #+#    #+#             */
/*   Updated: 2024/09/08 17:39:15 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool steps_from_wall(t_shared_data *data, t_p_pos pos)
{
	float move_step;
	int i;
	t_p_pos	real;
	t_p_pos new;

	i = 0;
	real = data->real_pos;
	float angle = data->player.rota_angle;
	while (i < 2)
	{
		move_step = (float)data->player.walk_dir * data->player.move_speed;
		new.x = (float)real.x + cos(angle)
			* (float)move_step;
		new.y = (float)real.y + sin(angle)
			* (float)move_step;
		pos.x = (int)floor(new.x / 32.0);
		pos.y = (int)floor(new.y / 32.0);
		if (data->game_env->map[(int)pos.y][(int)pos.x] == '1')
			return (false);
		real.x = new.x;
		real.y = new.y;
		i++;
	}
	return true;
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
	index = NUM_RAYS / 2;
	if ((data->player.walk_dir == 1 && data->rays && data->rays[index].distance > 20))
		return (true);
	else if (data->player.walk_dir == 1)
		return (false);
	else if (data->player.walk_dir == -1)
	{
		return steps_from_wall(data, pos);
	}
	return (false);
}
