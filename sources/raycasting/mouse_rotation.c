/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_rotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:36:55 by amejdoub          #+#    #+#             */
/*   Updated: 2024/09/07 15:41:17 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_loop(void *data)
{
    static int last_x = WIDTH / 2;
	static int i = 0;
    int current_x = WIDTH / 2, current_y = HEIGHT / 2;
    int screen_center_x = WIDTH / 2;
    int screen_center_y = HEIGHT / 2;

	if (i > 1)
    	mlx_get_mouse_pos(((t_shared_data *)data)->mlx, &current_x, &current_y);
    int delta_x = current_x - last_x;
    if (delta_x != 0)
    {
        ((t_shared_data *)data)->player.rota_angle += delta_x * 0.01;
		((t_shared_data *)data)->player.rota_angle = norm_angle(((t_shared_data *)data)->player.rota_angle);
    }
    last_x = current_x;
    mlx_set_mouse_pos(((t_shared_data *)data)->mlx, screen_center_x, screen_center_y);
    last_x = screen_center_x;
    render_map(data);
	if (i < 2)
		i++;
}