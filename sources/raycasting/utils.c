/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:25:01 by amejdoub          #+#    #+#             */
/*   Updated: 2024/08/11 16:01:43 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int degree_to_raidian(int dg)
{
    return (dg * (PI / 180));
}

int ray_angle()
{
    int fov = degree_to_raidian(60);
    return (fov / NUM_RAYS);
}