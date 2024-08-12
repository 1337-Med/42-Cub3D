/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:22:31 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/08/12 21:39:43 by nbenyahy         ###   ########.fr       */
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
