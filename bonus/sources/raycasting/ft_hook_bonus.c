/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 19:18:14 by amejdoub          #+#    #+#             */
/*   Updated: 2024/09/29 13:04:40 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_hook(void *param)
{
	t_shared_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		movement_a(data);
		return ;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		movement_d(data);
		return ;
	}
	walkturn_dir(data);
	calcul_new_cord(data);
	render_map(data);
}
