/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:39:13 by amejdoub          #+#    #+#             */
/*   Updated: 2024/09/07 15:39:20 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char **minimap_parse(t_shared_data *data)
{
	int p_x = (int )floor((data->real_pos.x) / 32);
	int p_y = (int )floor((data->real_pos.y) / 32);
	int start = p_y;
	int  end = p_y;
	int i = 0;
	while (i < 10)
	{
		if (!start)
			break ;
		start--;
		i++;
	}
	data->p_pos.y = (data->real_pos.y - (start * 32));
	int lim = 10;
	if (i != 10)
		lim += 10 - i;
	i = 0;
	while (i < lim)
	{
		if (end >= (int)ft_arrsize(data->game_env->map) || !data->game_env->map[end])
			break ;
		end++;
		i++;
	}
	char **mini_map = NULL;
	mini_map = ft_alloc(sizeof(char *) * (end - start + 1), mini_map, MALLOC);
	i = 0;
	int lim2 = -10;
	while (start + i < end)
	{
		lim = 20;
		lim2 = -10;
		int index = p_x + lim2;
		if (index < 0)
			index = 0;
		mini_map[i] = ft_substr(data->game_env->map[start + i], index, lim);
		if (i + start == p_y)
			data->p_pos.x = ((data->real_pos.x - (index * 32)));
		i++;
	}
	mini_map[i] = NULL;
	return (mini_map);
}