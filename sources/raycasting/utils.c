/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:25:01 by amejdoub          #+#    #+#             */
/*   Updated: 2024/09/08 18:34:32 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int degree_to_raidian(float dg)
{
    return (dg * (PI / 180));
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
            if (ft_strchr("NWSE", map[(int)pos.y][(int)pos.x]))
            {
                return (pos);
            }
            pos.x++;
        }
        pos.y++;
    }
    return pos;
}

float	distance_two_p(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

float	norm_angle(float angle)
{
	angle = fmod(angle, (2 * PI));
	if (angle < 0)
	{
		angle = (PI * 2) + angle;
	}
	return (angle);
}