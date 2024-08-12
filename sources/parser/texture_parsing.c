/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:35:30 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/08/12 21:39:55 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void setup_wall(mlx_texture_t** wall, char *s)
{
	char *trimed;

	if (*wall)
		free_print("invalid data. symbol is duplicated\n");
	if (ft_strncmp(s + (ft_strlen(s) - 4), ".png", 4))
		free_print("invalid format. shoude be end with .png\n");
	trimed = ft_strtrim(s, " \n\t\v");
	*wall = mlx_load_png(trimed);
	if (!*wall)
		free_print("error while loading.\n");
	ft_alloc(0, trimed, FREE_PTR);
}

bool check_rgb_format(char *s)
{
	int	i = 0;
	int j = 0;

	while (j < 2)
	{
		if (s[i] == '+')
			i++;
		while (s[i] && ft_isdigit(s[i]))
			i++;
		if (!s[i] || s[i] != ',')
			return (false);
		i++;
		while (s[i] && s[i] == ' ')
			i++;
		if (!s[i] || (!ft_isdigit(s[i]) && s[i] != '-' && s[i] != '+'))
			return (false);
		j++;
	}
	if (s[i] == '+')
		i++;
	while (s[i] && ft_isdigit(s[i]))
		i++;
	if (s[i])
		return (false);
	return (true);
}

int calculate_colors(char *s)
{
	char **rgba;
	int	color;
	
	rgba = ft_split(s, ',');
	color = 0;
	if (ft_arrsize(rgba) != 3 && ft_arrsize(rgba) != 4)
		free_print("invalid rgba colors\n");
	if (ft_arrsize(rgba) == 3)
		color = get_rgba(ft_atoi(rgba[0]), ft_atoi(rgba[1]), ft_atoi(rgba[2]), 1);
	else if (ft_arrsize(rgba) == 4)
		color = get_rgba(ft_atoi(rgba[0]), ft_atoi(rgba[1]), ft_atoi(rgba[2]), ft_atoi(rgba[3]));
	ft_alloc(0, rgba, FREE_PTR);
	return (color);
}

void save_earth_sky(char **arr, t_game_env **game_env)
{
	char *trimed;

	if (ft_strlen(arr[0]) == 1 && !ft_strncmp(arr[0], "F", ft_strlen(arr[0])))
	{
		if ((*game_env)->floor != -1)
			free_print("invalid data. symbol is duplicated\n");
		trimed = ft_strtrim(arr[1], " \n\t\v");
		if (!check_rgb_format(trimed))
			free_print("invalid rgb format. soulde be like 255,255,255 \n");
		(*game_env)->floor = calculate_colors(trimed);
	}
	if (ft_strlen(arr[0]) == 1 && !ft_strncmp(arr[0], "C", ft_strlen(arr[0])))
	{
		if ((*game_env)->ceiling != -1)
			free_print("invalid data. symbol is duplicated\n");
		trimed = ft_strtrim(arr[1], " \n\t\v");
		if (!check_rgb_format(trimed))
			free_print("invalid rgb format. soulde be like 255,255,255 \n");
		(*game_env)->ceiling = calculate_colors(trimed);
	}
}

void save_walls(char **arr, t_game_env **game_env)
{
	if (ft_strlen(arr[0]) == 2 && !ft_strncmp(arr[0], "NO", ft_strlen(arr[0])))
		setup_wall(&(*game_env)->wall->north, arr[1]);
	else if (ft_strlen(arr[0]) == 2 && !ft_strncmp(arr[0], "SO", ft_strlen(arr[0])))
		setup_wall(&(*game_env)->wall->south, arr[1]);
	else if (ft_strlen(arr[0]) == 2 && !ft_strncmp(arr[0], "WE", ft_strlen(arr[0])))
		setup_wall(&(*game_env)->wall->west, arr[1]);
	else if (ft_strlen(arr[0]) == 2 && !ft_strncmp(arr[0], "EA", ft_strlen(arr[0])))
		setup_wall(&(*game_env)->wall->east, arr[1]);
}
