/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:52:51 by amejdoub          #+#    #+#             */
/*   Updated: 2024/11/01 12:21:15 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void ll()
{
	system("leaks -q cub3D_bonus");
}

int	main(int ac, char **av)
{
	// atexit(ll);
	raycaster(parser(ac, av));
	return (0);
}
