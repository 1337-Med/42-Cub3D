/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:48:01 by amejdoub          #+#    #+#             */
/*   Updated: 2024/09/04 18:49:01 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_ray(t_shared_data *data, int i, float ray_angle)
{
	data->rays[i].angle = norm_angle(ray_angle);
		data->rays[i].wall_hit_x = 0;
		data->rays[i].wall_hit_y = 0;
		data->rays[i].ray_p.x = 0;
		data->rays[i].ray_p.y = 0;
		data->rays[i].horiz_x = -1;
		data->rays[i].horiz_y = -1;
		data->rays[i].vert_x = -1;
		data->rays[i].vert_y = -1;
		data->rays[i].distance = 0;
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
}
void	create_rays(t_shared_data *data)
{
	int		i;
	float	ray_angle;

	i = 0;
	ray_angle = (norm_angle(data->player.rota_angle)) - (FOV / 2);
	data->rays = NULL;
	data->rays = ft_alloc(sizeof(t_rays) * (NUM_RAYS + 1), data->rays, CALLOC);
	while (i < NUM_RAYS)
	{
		init_ray(data, i, ray_angle);
		i++;
		ray_angle += (float)(FOV / NUM_RAYS);
	}
}
