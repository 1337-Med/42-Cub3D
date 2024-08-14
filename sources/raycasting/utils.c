/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:25:01 by amejdoub          #+#    #+#             */
/*   Updated: 2024/08/14 16:53:59 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int degree_to_raidian(float dg)
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
    while (map[(int)pos.y])
    {
        pos.x = 0;
        while (map[(int)pos.y][(int)pos.x])
        {
            if (map[(int)pos.y][(int)pos.x] == 'N')
            {
                // printf (" %d %d\n", pos.y , pos.x);
                return (pos);
            }
            if (map[(int)pos.y][(int)pos.x] == 'W')
                return (pos);
            if (map[(int)pos.y][(int)pos.x] == 'E')
                return (pos);
            if (map[(int)pos.y][(int)pos.x] == 'S')
                return (pos);
            pos.x++;
        }
        pos.y++;
    }
    printf ("hihii\n");
    return pos;
}