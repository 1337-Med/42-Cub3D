/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:39:13 by amejdoub          #+#    #+#             */
/*   Updated: 2024/10/13 12:48:03 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	calculate_start(t_shared_data *data, int *start)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (!*start)
			break ;
		(*start)--;
		i++;
	}
	data->p_pos.y = (data->real_pos.y - (*start * 32)) - 12;
	return (i);
}

int	calculate_end(t_shared_data *data, int *end, int i)
{
	int	lim;

	lim = 7;
	while (i < lim + i && i < 14)
	{
		if (*end >= (int)ft_arrsize(data->game_env->map)
			|| !data->game_env->map[*end])
			break ;
		(*end)++;
		i++;
	}
	return (i);
}

char	**fill_map(t_shared_data *data, int start, int end, t_cord p)
{
	char	**mini_map;
	int		i;
	int		lim;
	int		lim2;
	int		index;

	i = 0;
	mini_map = NULL;
	mini_map = ft_alloc(sizeof(char *) * (end - start + 1), mini_map, MALLOC);
	while (start + i < end)
	{
		lim = 20;
		lim2 = -10;
		index = p.x + lim2;
		if (index < 0)
			index = 0;
		mini_map[i] = ft_substr(data->game_env->map[start + i], index, lim);
		if (i + start == p.y)
			data->p_pos.x = ((data->real_pos.x - (index * 32))) - 12;
		i++;
	}
	mini_map[i] = NULL;
	return (mini_map);
}

char	**minimap_parse(t_shared_data *data)
{
	t_cord	p;
	int		start;
	int		end;
	int		i;

	p.x = (int)floor((data->p_pos.x) / 32);
	p.y = (int)floor((data->p_pos.y) / 32);
	start = p.y;
	end = p.y;
	i = 0;
	i = calculate_start(data, &start);
	i = calculate_end(data, &end, i);
	return (fill_map(data, start, end, p));
}
