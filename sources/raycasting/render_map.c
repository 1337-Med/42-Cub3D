/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:43:22 by amejdoub          #+#    #+#             */
/*   Updated: 2024/09/07 15:44:20 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	DDA(float x1, float y1, float x2, float y2, mlx_image_t *image)
{
	float	dx;
	float	dy;
	float	steps;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;

	dx = x2 - x1;
	dy = y2 - y1;
	steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	x_inc = dx / (float)steps;
	y_inc = dy / (float)steps;
	x = x1;
	y = y1;
	mlx_put_pixel(image, round(x), round(y), 0xFFFFFFFF);
	for (int i = 0; i < steps; i++)
	{
		x += x_inc;
		y += y_inc;
		if (y < HEIGHT && y > 0 && x < WIDTH && x > 0)
			mlx_put_pixel(image, round(x), round(y), 0xFFFFFFFF);
	}
}

void	render_map(t_shared_data *data)
{
	int		i;
	int		p;
	float	distancepp;
	float	wall_height;
	int		wall_top;
	int		wall_bottom;
	int		x;
	int		y;
	char **mini_map = NULL;

	create_rays(data);
	cast_rays(data, NUM_RAYS);
	i = 0;
	while (i < HEIGHT)
	{
		p = 0;
		while (p < WIDTH)
		{
			if (i < HEIGHT / 2)
				mlx_put_pixel(data->image, p, i, data->game_env->ceiling);
			else
				mlx_put_pixel(data->image, p, i, data->game_env->floor);
			p++;
		}
		i++;
	}
	i = 0;
	while (i < NUM_RAYS)
	{
		if (data->rays[i].distance == 0)
			data->rays[i].distance = 0.5;
		distancepp = (WIDTH / 2) / tan(FOV / 2);
		wall_height = (32 / data->rays[i].distance) * distancepp;
		wall_top = (HEIGHT / 2) - (wall_height / 2);
		wall_bottom = (HEIGHT / 2) + (wall_height / 2);
		rander_textures(data, i, wall_top, wall_bottom);
		i++;
	}
	mini_map = minimap_parse(data);
	x = 0;
	y = 0;
	while (y < 193)
	{
		x = 0;
		while (x < 257)
		{
			mlx_put_pixel(data->image, x, y, data->game_env->floor);
			x++;
		}
		y++;
	}
	y = 0;
	while (mini_map[y])
	{
		x = 0;
		while (mini_map[y][x])
		{
			if (mini_map[y][x] == '1')
				render_rec(y, x, data->image, 'W');
			if (mini_map[y][x] == '0'
				|| mini_map[y][x] == 'N')
				render_rec(y, x, data->image, 'F');
			x++;
		}
		y++;
	}
	mlx_put_pixel(data->image, data->p_pos.x * MINI_FACTOR, data->p_pos.y * MINI_FACTOR, 0xFFFFFFFF);
	DDA(data->p_pos.x * MINI_FACTOR, data->p_pos.y * MINI_FACTOR, data->p_pos.x * MINI_FACTOR + 50 * cos(data->player.rota_angle),
	data->p_pos.y * MINI_FACTOR + 50 * sin(data->player.rota_angle), data->image);
	i = 0;
	while (mini_map && mini_map[i])
		ft_alloc( 0, mini_map[i++], FREE_PTR);
	ft_alloc(0,mini_map, FREE_PTR);
}