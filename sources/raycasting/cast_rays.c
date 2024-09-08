/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:49:56 by amejdoub          #+#    #+#             */
/*   Updated: 2024/09/08 18:42:58 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	choose_smaller(t_shared_data *data, int i, char c, float chosen)
{
	if (c == 'V')
	{
		data->rays[i].distance = chosen;
		data->rays[i].distance = data->rays[i].distance
			* cos(data->rays[i].angle - data->player.rota_angle);
		data->rays[i].ray_p.x = data->rays[i].vert_x;
		data->rays[i].ray_p.y = data->rays[i].vert_y;
		data->rays[i].ray_down = 0;
		data->rays[i].ray_up = 0;
	}
	else
	{
		data->rays[i].distance = chosen;
		data->rays[i].distance = data->rays[i].distance
			* cos(data->rays[i].angle - data->player.rota_angle);
		data->rays[i].ray_p.x = data->rays[i].horiz_x;
		data->rays[i].ray_p.y = data->rays[i].horiz_y;
		data->rays[i].ray_left = 0;
		data->rays[i].ray_right = 0;
	}
}

void	smaller_distance(t_shared_data *data, int i, float horz, float vertical)
{
	if ((int)data->rays[i].horiz_x == -1)
		choose_smaller(data, i, 'V', vertical);
	else if ((int)data->rays[i].vert_x == -1)
		choose_smaller(data, i, 'H', horz);
	else if ((int)data->rays[i].horiz_x != -1 && (int)data->rays[i].vert_x != \
		-1)
	{
		if (horz <= vertical)
			choose_smaller(data, i, 'H', horz);
		else
			choose_smaller(data, i, 'V', vertical);
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
		smaller_distance(data, i, horz, vertical);
		i++;
	}
}
