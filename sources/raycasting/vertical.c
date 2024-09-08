/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:53:36 by amejdoub          #+#    #+#             */
/*   Updated: 2024/09/08 18:05:15 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void v_stepinter(t_shared_data *data, int i, t_p_pos *inter, t_p_pos *step)
{
	inter->x = floor(data->real_pos.x / 32) * 32;
	if (data->rays[i].ray_right)
		inter->x += 32;
	inter->y = data->real_pos.y + ((inter->x - data->real_pos.x)
			* tan(data->rays[i].angle));
	step->x = 32;
	if (data->rays[i].ray_left)
		step->x = -step->x;
	step->y = step->x * tan(data->rays[i].angle);
	if (data->rays[i].ray_up && step->y > 0)
		step->y = -step->y;
	if (data->rays[i].ray_down && step->y < 0)
		step->y = -step->y;
}

bool v_wall_found(t_shared_data *data, t_cord map, int i, t_p_pos inter)
{
    if (data->game_env->map[map.y])
	{
			if (data->game_env->map[map.y][map.x] == '1')
			{
				data->rays[i].vert_x = inter.x;
				data->rays[i].vert_y = inter.y;
				return true;
			}
	}
    return false;
}

void	get_vertical_inter(t_shared_data *data, int i)
{
	t_p_pos inter;
	t_p_pos step;
	float	touch_x;
	t_cord map;

	v_stepinter(data, i, &inter, &step);
	while (inter.y > 0 && inter.x > 0)
	{
		touch_x = inter.x;
		if (data->rays[i].ray_left)
			touch_x--;
		map.y = (int)floor((inter.y / 32));
		map.x = (int)floor((touch_x / 32));
		if (map.y < 0 || map.y >= (int)ft_arrsize(data->game_env->map)
			|| map.x < 0 || map.x >= (int)ft_strlen(data->game_env->map[map.y]))
		{
			data->rays[i].vert_x = -1;
			data->rays[i].vert_y = -1;
			return ;
		}
		if (v_wall_found(data, map, i, inter))
			return ;
		inter.y += step.y;
		inter.x += step.x;
	}
}
