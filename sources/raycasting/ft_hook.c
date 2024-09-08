/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 19:18:14 by amejdoub          #+#    #+#             */
/*   Updated: 2024/09/08 19:19:17 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_hook(mlx_key_data_t key, void *param)
{
	t_shared_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (key.key == MLX_KEY_A && mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		movement_a(data);
		return ;
	}
	if (key.key == MLX_KEY_D && mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		movement_d(data);
		return ;
	}
	walkturn_dir(data, key);
	calcul_new_cord(data);
	render_map(data);
}
