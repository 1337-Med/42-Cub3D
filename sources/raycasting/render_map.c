/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:43:22 by amejdoub          #+#    #+#             */
/*   Updated: 2024/09/08 18:36:59 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rander_sky_floor(t_shared_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			if (i < HEIGHT / 2)
				mlx_put_pixel(data->image, j, i, data->game_env->ceiling);
			else
				mlx_put_pixel(data->image, j, i, data->game_env->floor);
			j++;
		}
		i++;
	}
}

void	minimap_backgrand(t_shared_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < 193)
	{
		j = 0;
		while (j < 257)
			mlx_put_pixel(data->image, j++, i, data->game_env->floor);
		i++;
	}
}

void	rander_minimap(t_shared_data *data)
{
	char	**mini_map;
	int		i;
	int		j;

	i = 0;
	mini_map = NULL;
	mini_map = minimap_parse(data);
	minimap_backgrand(data);
	while (mini_map[i])
	{
		j = 0;
		while (mini_map[i][j])
		{
			if (mini_map[i][j] == '1')
				render_rec(i, j, data->image, 'W');
			if (ft_strchr("0NSWE", mini_map[i][j]))
				render_rec(i, j, data->image, 'F');
			j++;
		}
		i++;
	}
	i = 0;
	while (mini_map && mini_map[i])
		ft_alloc(0, mini_map[i++], FREE_PTR);
	ft_alloc(0, mini_map, FREE_PTR);
}

void	render_map(t_shared_data *data)
{
	float	wall_hgt;
	int		wall_top;
	int		wall_bottom;
	int		i;

	create_rays(data);
	cast_rays(data, NUM_RAYS);
	rander_sky_floor(data);
	i = 0;
	while (i < NUM_RAYS)
	{
		if (data->rays[i].distance == 0)
			data->rays[i].distance = 0.5;
		wall_hgt = (32 / data->rays[i].distance) * ((WIDTH / 2) / tan(FOV / 2));
		wall_top = (HEIGHT / 2) - (wall_hgt / 2);
		wall_bottom = (HEIGHT / 2) + (wall_hgt / 2);
		rander_textures(data, i++, wall_top, wall_bottom);
	}
	rander_minimap(data);
	render_player(data);
}
