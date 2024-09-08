/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:22:01 by amejdoub          #+#    #+#             */
/*   Updated: 2024/09/08 18:41:28 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_player(t_shared_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < 10)
	{
		x = 0;
		while (x < 10)
		{
			mlx_put_pixel(data->image, (data->p_pos.x + x) * MINI_FACTOR,
				(data->p_pos.y + y) * MINI_FACTOR, 0xFFFFFFFF);
			x++;
		}
		y++;
	}
}
