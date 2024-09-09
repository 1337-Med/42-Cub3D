/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arradd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:56:43 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/09/09 11:38:38 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arradd_back(char **arr, char *new_str)
{
	int		i;
	char	**new;

	i = 0;
	while (arr && arr[i])
		i++;
	new = ft_alloc((sizeof(char *) * (i + 2)), NULL, MALLOC);
	if (!new)
		return (NULL);
	i = 0;
	while (arr && arr[i])
	{
		new[i] = ft_strdup(arr[i]);
		i++;
	}
	new[i] = ft_strdup(new_str);
	new[i + 1] = NULL;
	ft_arrclean(arr);
	return (new);
}
