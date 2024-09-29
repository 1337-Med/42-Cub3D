/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rander_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:42:40 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/09/29 12:32:45 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	texture_to_img(t_shared_data *data)
{
	data->game_env->side = ft_alloc(sizeof(t_side), data->game_env->side,
			MALLOC);
	data->game_env->side->east = mlx_texture_to_image(data->mlx,
			data->game_env->wall->east);
	data->game_env->side->north = mlx_texture_to_image(data->mlx,
			data->game_env->wall->north);
	data->game_env->side->south = mlx_texture_to_image(data->mlx,
			data->game_env->wall->south);
	data->game_env->side->west = mlx_texture_to_image(data->mlx,
			data->game_env->wall->west);
	if (!data->game_env->side->east || !data->game_env->side->north
		|| !data->game_env->side->south || !data->game_env->side->west)
		free_print("error while converting png to texture\n",
			data->game_env->wall);
}

int	get_pixel(mlx_image_t *image, int x, int y)
{
	int		pixel_index;
	uint8_t	*pixel_data;
	int		pixel_color;

	if (x < 0 || x >= (int)image->width || y < 0 || y >= (int)image->height)
		return (0);
	pixel_index = (y * image->width * 4) + x * 4;
	pixel_data = &image->pixels[pixel_index];
	pixel_color = pixel_data[0] << 24 | pixel_data[1] << 16 \
					| pixel_data[2] << 8 | pixel_data[3];
	return (pixel_color);
}
#include <stdio.h>
void	draw_line_pixel(int *tb, int i,
		t_shared_data *data, int tex_x)
{
	int	tex_y;
	int	line_dis;
	int	j;

	line_dis = tb[1] - tb[0];
	j = tb[0];
	int start = MAX(0, tb[0]);
	int end = MIN(HEIGHT, tb[1]);
	j = start;
	while (j < end)
	{
		tex_y = ((j - tb[0]) * data->target_img->height) / line_dis;
			mlx_put_pixel(data->image, i, j, \
							get_pixel(data->target_img, tex_x, tex_y));
		
		j++;
	}
}

void	rander_textures(t_shared_data *data, int i, int wall_top,
		int wall_bottom)
{
	int		tex_x;
	float	wall_hit;

	tex_x = 0;
	wall_hit = 0.0;
	if (data->rays[i].ray_right || data->rays[i].ray_left)
	{
		if (data->rays[i].ray_right)
			data->target_img = data->game_env->side->west;
		else
			data->target_img = data->game_env->side->east;
		wall_hit = data->rays[i].ray_p.y / 32.0 \
					- floor(data->rays[i].ray_p.y / 32.0);
	}
	else if (data->rays[i].ray_up || data->rays[i].ray_down)
	{
		if (data->rays[i].ray_up)
			data->target_img = data->game_env->side->south;
		else
			data->target_img = data->game_env->side->north;
		wall_hit = data->rays[i].ray_p.x / 32.0 \
					- floor(data->rays[i].ray_p.x / 32.0);
	}
	tex_x = (int)(wall_hit * (float)data->target_img->width);
	// while (wall_top < wall_bottom)
	// 	{
	// 		if (wall_top < HEIGHT && wall_top > 0)
	// 		{

	// 		// write(1, "test\n", 6);
	// 			mlx_put_pixel(data->image, i, wall_top, 0);
	// 		}
	// 		wall_top++;
	// 	}
	draw_line_pixel((int [2]){wall_top, wall_bottom}, i, data, tex_x);
}
