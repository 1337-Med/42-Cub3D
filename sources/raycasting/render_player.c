/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:22:01 by amejdoub          #+#    #+#             */
/*   Updated: 2024/09/22 16:30:33 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_player(t_shared_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < 22)
	{
		x = 0;
		while (x < 22)
		{
			if (x > 9 && x < 14 && y > 9 && y < 14)
				mlx_put_pixel(data->image, (data->p_pos.x + x) * MINI_FACTOR,
					(data->p_pos.y + y) * MINI_FACTOR, 0);
			else
				mlx_put_pixel(data->image, (data->p_pos.x + x) * MINI_FACTOR,
					(data->p_pos.y + y) * MINI_FACTOR, 0xFFFFFFFF);
			x++;
		}
		y++;
	}
}
