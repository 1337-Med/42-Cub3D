/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycatser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:19:40 by amejdoub          #+#    #+#             */
/*   Updated: 2024/08/12 13:05:05 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int raycaster(char **map)
{
    (void)map;
    int y = 0;
    int x = 0;
    mlx_t *mlx;
    void *mlx_win;
    // void *img;
    mlx = mlx_init(600, 600, "MLX42", true);
    mlx_image_t* image;
    image = mlx_new_image(mlx, 128, 128);
    mlx_image_to_window(mlx, image, 0, 0);

    // mlx = mlx_init();
    // mlx_win = mlx_new
    mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
    return 0;
}