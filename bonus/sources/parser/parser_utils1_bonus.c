/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:53:23 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/09/29 13:03:41 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	check_empty_line(char *line)
{
	char	*s;

	if (ft_strlen(line) == 1 && !ft_strncmp(line, "\n", ft_strlen(line)))
	{
		ft_alloc(0, line, FREE_PTR);
		return (1);
	}
	s = ft_strtrim(line, " \t\n");
	if (s[0] == '\0')
	{
		ft_alloc(0, line, FREE_PTR);
		ft_alloc(0, s, FREE_PTR);
		return (1);
	}
	ft_alloc(0, s, FREE_PTR);
	return (0);
}

void	skip_spaces(int *i, char *s)
{
	while (s[*i] && (s[*i] == ' ' || s[*i] == '\t'))
		(*i)++;
}
