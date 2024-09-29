/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_condition_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:28:51 by amejdoub          #+#    #+#             */
/*   Updated: 2024/09/29 15:45:44 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	while (i < 5)
	{
		move_step = (float)data->player.walk_dir * data->player.move_speed;
		new.x = (float)real.x + cos(angle) * (float)move_step;
		new.y = (float)real.y + sin(angle) * (float)move_step;
		pos.x = (int)floor(new.x / 32.0);
		pos.y = (int)floor(new.y / 32.0);
		if (data->game_env->map[(int)pos.y][(int )floor(real.x / 32)] == '1' \
		|| data->game_env->map[(int )floor(real.y / 32)][(int )pos.x] == '1' \
		|| data->game_env->map[(int)pos.y][(int)pos.x] == '1')
			return (false);
		real.x = new.x;
		real.y = new.y;
		i++;
	}
	return (true);
}

bool	move_up_condition(t_shared_data *data)
{
	t_p_pos	pos;

	pos.x = 0;
	if (data->player.walk_dir != 0)
	{
		return (steps_from_wall(data, pos));
	}
	return (false);
}
