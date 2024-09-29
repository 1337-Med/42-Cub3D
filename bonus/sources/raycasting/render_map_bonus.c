/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:43:22 by amejdoub          #+#    #+#             */
/*   Updated: 2024/09/29 13:04:53 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	while (i < 183)
	{
		j = 0;
		while (j < 257)
		{
			if (j == 0 || j == 256 || i == 0 || i == 182)
				mlx_put_pixel(data->image, j, i, 0x910910FF);
			else
				mlx_put_pixel(data->image, j, i, 0x6991e0FF);
			
			j++;
		}
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
		// while (wall_top < wall_bottom)
		// {
		// 	if (wall_top < HEIGHT && wall_top > 0)
		// 	{

		// 	// write(1, "test\n", 6);
		// 		mlx_put_pixel(data->image, i, wall_top, 0);
		// 	}
		// 	wall_top++;
		// }
		// i++;
		rander_textures(data, i++, wall_top, wall_bottom);
	}
	rander_minimap(data);
	render_player(data);
}
