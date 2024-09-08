/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:19:40 by amejdoub          #+#    #+#             */
/*   Updated: 2024/09/08 17:16:14 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_raycaster(t_shared_data *data, t_game_env *game_env)
{
	data->rays = NULL;
	data->game_env = game_env;
	data->p_pos = get_player_pos(data->game_env->map);
	data->real_pos = get_player_pos(data->game_env->map);
	data->real_pos.x = (data->real_pos.x * 32) + 16;
	data->real_pos.y = (data->real_pos.y * 32) + 16;
	data->player.pos = data->real_pos;
	data->player.raduis = 3;
	data->player.walk_dir = 0;
	data->player.turn_dir = 0;
	if (game_env->dir == 'N')
		data->player.rota_angle =   (3 * PI) / 2;
	if (game_env->dir == 'S')
		data->player.rota_angle =  PI / 2;
	if (game_env->dir == 'W')
		data->player.rota_angle =  PI;
	if (game_env->dir == 'E')
		data->player.rota_angle =  0;
	data->player.move_speed = 8;
	data->player.rotate_speed = 4 * (PI / 180);
	data->mlx = NULL;
	data->image = NULL;
}

void init_mlx(t_shared_data *data)
{
	if (!(data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", false)))
	{
		puts(mlx_strerror(mlx_errno));
		exit (EXIT_FAILURE);
	}
	if (!(data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		exit (EXIT_FAILURE);
	}
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		exit (EXIT_FAILURE);
	}
}

int	raycaster(t_game_env *game_env)
{
	t_shared_data	data;

	init_raycaster(&data, game_env);
	init_mlx(&data);
	create_rays(&data);
	texture_to_img(&data);
	render_map(&data);
	mlx_set_cursor_mode(data.mlx, MLX_MOUSE_HIDDEN);
    mlx_set_mouse_pos(data.mlx, WIDTH / 2, HEIGHT / 2);
	mlx_key_hook(data.mlx, ft_hook, &data);
	mlx_loop_hook(data.mlx, ft_loop, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
