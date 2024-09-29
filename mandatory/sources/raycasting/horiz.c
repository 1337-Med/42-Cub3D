/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horiz.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:24:29 by amejdoub          #+#    #+#             */
/*   Updated: 2024/09/29 16:42:56 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	h_set_step_inter(t_shared_data *data, int i, t_p_pos *inter,
		t_p_pos *step)
{
	inter->y = floor(data->real_pos.y / 32) * 32;
	if (data->rays[i].ray_down)
		inter->y += 32;
	inter->x = data->real_pos.x + ((inter->y - data->real_pos.y)
			/ tan(data->rays[i].angle));
	step->y = 32;
	if (data->rays[i].ray_up)
		step->y = -step->y;
	step->x = step->y / tan(data->rays[i].angle);
	if ((data->rays[i].ray_left && step->x > 0) || (data->rays[i].ray_right
			&& step->x < 0))
		step->x = -step->x;
}

bool	wall_found(t_shared_data *data, t_cord map, int i, t_p_pos inter)
{
	if (data->game_env->map[map.y])
	{
		if (data->game_env->map[map.y][map.x] == '1')
		{
			data->rays[i].horiz_x = inter.x;
			data->rays[i].horiz_y = inter.y;
			return (true);
		}
	}
	return (false);
}

void	get_horizontal_inter(t_shared_data *data, int i)
{
	t_p_pos	inter;
	t_p_pos	step;
	float	touch_y;
	t_cord	map;

	h_set_step_inter(data, i, &inter, &step);
	while (inter.y > 0 && inter.x > 0 && inter.y < HEIGHT)
	{
		touch_y = inter.y;
		if (data->rays[i].ray_up)
			touch_y--;
		map.y = floor(touch_y / 32);
		map.x = floor(inter.x / 32);
		if (map.y < 0 || map.y >= (int)ft_arrsize(data->game_env->map)
			|| map.x < 0 || map.x > (int)ft_strlen(data->game_env->map[map.y]))
		{
		 write(1, "err\n", 5);
			data->rays[i].horiz_x = -1;
			data->rays[i].horiz_y = -1;
			return ;
		}
		if (wall_found(data, map, i, inter))
			return ;
		inter.y += step.y;
		inter.x += step.x;
	}
}
