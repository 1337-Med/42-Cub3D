/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:25:01 by amejdoub          #+#    #+#             */
/*   Updated: 2024/08/12 21:30:22 by amejdoub         ###   ########.fr       */
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

t_p_pos get_player_pos(char **map)
{
    t_p_pos pos;
    pos.y = 0;
    while (map[pos.y])
    {
        pos.x = 0;
        while (map[pos.y][pos.x])
        {
            if (map[pos.y][pos.x] == 'N')
            {
                printf (" %d %d\n", pos.y , pos.x);
                return (pos);
            }
            if (map[pos.y][pos.x] == 'W')
                return (pos);
            if (map[pos.y][pos.x] == 'E')
                return (pos);
            if (map[pos.y][pos.x] == 'S')
                return (pos);
            pos.x++;
        }
        pos.y++;
    }
    printf ("hihii\n");
    return pos;
}