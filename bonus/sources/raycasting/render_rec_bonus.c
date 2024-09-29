/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_rec_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:30:13 by amejdoub          #+#    #+#             */
/*   Updated: 2024/09/29 13:04:58 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	render_rec(int y, int x, mlx_image_t *image, char c)
{
	int		start_y;
	int		start_x;
	int		color;
	float	i;
	float	j;

	color = 0x0000000;
	start_y = y * 32 * MINI_FACTOR;
	start_x = x * 32 * MINI_FACTOR;
	if (c == 'W')
		color = 0;
	else if (c == 'F')
		color = 0xFFFFFFFF;
	i = 0;
	j = 0;
	while (i < 32 * MINI_FACTOR)
	{
		j = 0;
		while (j < 32 * MINI_FACTOR)
		{
			mlx_put_pixel(image, start_x + j, start_y + i, color);
			j++;
		}
		i++;
	}
}
