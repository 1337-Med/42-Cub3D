/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_rotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:36:55 by amejdoub          #+#    #+#             */
/*   Updated: 2024/09/08 15:49:25 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_loop(void *data)
{
	static int	i = 0;
	int			current_x;
	int			current_y;
	int			delta_x;

	current_x = WIDTH / 2;
	current_y = HEIGHT / 2;
	if (i > 1)
		mlx_get_mouse_pos(((t_shared_data *)data)->mlx, &current_x, &current_y);
	delta_x = current_x - WIDTH / 2;
	if (delta_x != 0)
	{
		((t_shared_data *)data)->player.rota_angle += delta_x * 0.01;
		((t_shared_data *)data)->player.rota_angle = \
		norm_angle(((t_shared_data *)data)->player.rota_angle);
	}
	mlx_set_mouse_pos(((t_shared_data *)data)->mlx, WIDTH / 2, HEIGHT / 2);
	render_map(data);
	if (i < 2)
		i++;
}
