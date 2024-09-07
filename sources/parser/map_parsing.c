/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:34:36 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/09/06 18:54:09 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	zero_pos(int *ij, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				ij[0] = i;
				ij[1] = j;
				return ;
			}
			j++;
		}
		i++;
	}
	ij[0] = -1;
	ij[1] = -1;
}

int	*player_position(char **map)
{
	int	j;
	int	i;
	int	*ij;

	ij = NULL;
	ij = ft_alloc(sizeof(int) * 2, ij, CALLOC);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW", map[i][j]))
			{
				ij[0] = i;
				ij[1] = j;
				return (ij);
			}
			j++;
		}
		i++;
	}
	zero_pos(ij, map);
	return (ij);
}

void	flod_fill_checker(char **map, int *xy, t_wall *wall)
{
	if ((xy[0] <= 0 || xy[1] <= 0 || xy[0] >= (int)ft_arrsize(map) - 1
			|| xy[1] >= (int)ft_strlen(map[xy[0]]) - 1)
		&& map[xy[0]][xy[1]] != '1')
		free_print("invalid map. The map must be closed/surrounded by walls\n",
			wall);
	if (map[xy[0]][xy[1]] == ' ' || map[xy[0]][xy[1]] == '\0')
		free_print("invalid map. The map must be closed/surrounded by walls\n",
			wall);
	else if (map[xy[0]][xy[1]] == '0')
	{
		map[xy[0]][xy[1]] = '1';
		flod_fill_checker(map, (int [2]){xy[0] + 1, xy[1]}, wall);
		flod_fill_checker(map, (int [2]){xy[0] - 1, xy[1]}, wall);
		flod_fill_checker(map, (int [2]){xy[0], xy[1] + 1}, wall);
		flod_fill_checker(map, (int [2]){xy[0], xy[1] - 1}, wall);
	}
	else
		return ;
}

void	check_map(char **map, t_wall *wall)
{
	char	**temp_map;
	int		*xy;
	int		i;

	temp_map = NULL;
	xy = NULL;
	temp_map = ft_alloc(sizeof(char *) * (ft_arrsize(map) + 1), \
				temp_map, CALLOC);
	i = 0;
	while (map[i])
	{
		temp_map[i] = ft_strdup(map[i]);
		i++;
	}
	temp_map[i] = NULL;
	while (1)
	{
		xy = player_position(temp_map);
		if (xy[0] == -1)
			break ;
		temp_map[xy[0]][xy[1]] = '0';
		flod_fill_checker(temp_map, xy, wall);
	}
	ft_alloc(0, xy, FREE_PTR);
	ft_alloc(0, temp_map, FREE_PTR);
}
