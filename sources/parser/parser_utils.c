/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:22:31 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/08/12 21:45:16 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_print(char *s)
{
	ft_alloc(0, NULL, FREE_ALL);
	print_err(1, s);
}

int get_rgba(int r, int g, int b, int a)
{
	if (r < 0  || r > 255 || g < 0  || g > 255 || b < 0  || b > 255)
		free_print("invalid numbers for rgb values\n");
    return (r << 24 | g << 16 | b << 8 | a);
}
char **spliter(char *line)
{
	char **arr;
	char *str;
	int i;

	arr = NULL;
	str = NULL;
	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	str = ft_substr(line, 0, i);
	arr = ft_arradd_back(arr, str);
	ft_alloc(0, str, FREE_PTR);
	while (line[i] && line[i] == ' ')
		i++;
	str = ft_substr(line, i, ft_strlen(line) - i - 1);
	arr = ft_arradd_back(arr, str);
	ft_alloc(0, str, FREE_PTR);
	return (arr);
}
void save_tools(char **arr, t_game_env **game_env)
{
	if (ft_arrsize(arr) != 2)
	{
		ft_alloc(0, NULL, FREE_ALL);
		print_err(1, "invalid data. split  and ther value by space\n");
	}
	if (ft_strlen(arr[0]) == 2 && \
		(!ft_strncmp(arr[0], "NO", ft_strlen(arr[0])) \
		|| !ft_strncmp(arr[0], "SO", ft_strlen(arr[0])) \
		|| !ft_strncmp(arr[0], "WE", ft_strlen(arr[0])) \
		|| !ft_strncmp(arr[0], "EA", ft_strlen(arr[0]))))
		save_walls(arr, game_env);
	else if (ft_strlen(arr[0]) == 1 && \
		(!ft_strncmp(arr[0], "F", ft_strlen(arr[0])) \
		|| !ft_strncmp(arr[0], "C", ft_strlen(arr[0]))))
		save_earth_sky(arr, game_env);
	else
	{
		ft_alloc(0, NULL, FREE_ALL);
		print_err(1, "invalid or missing data\n");
	}
}
