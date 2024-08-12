/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:19:40 by amejdoub          #+#    #+#             */
/*   Updated: 2024/08/12 18:00:30 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render_rec(int y, int x, mlx_image_t* image, char c)
{
    int start_y = y * 32;
    int start_x = x * 32;
    int color;
    if (c == 'W')
        color = 0xFF0000FF ;
    else if (c == 'F')
        color = 0x02f7b2;
    int i = 0;
    int j = 0;
    while (i < 32)
    {
        j = 0;
        while (j < 32)
        {
            mlx_put_pixel(image, start_x + j, start_y + i, color);
            j++;
        }
        i++;
    }
}
void render_player(int y, int x, mlx_image_t* image)
{
    int start_y = y * 32;
    int start_x = x * 32;
    int color = 0xFFFFFFFF;

    int i = 0;
    int j = 0;
    while (i < 32)
    {
        j = 0;
        while (j < 32)
        {
            mlx_put_pixel(image, start_x + j, start_y + i, color);
            j++;
        }
        i++;
    }
}
void rander_map (t_game_env *game_env, mlx_image_t* image)
{
    int x = 0;
    int y = 0;
    while (game_env->map[y])
    {
        x = 0;
        while (game_env->map[y][x])
        {
            if (game_env->map[y][x] == '1')
                render_rec(y, x, image, 'W');
            if (game_env->map[y][x] == '0')
            {
                render_rec(y, x, image, 'F');
            }
            if (game_env->map[y][x] == 'N')
            {
                render_player(y, x, image);
            }
            x++;
        }
        y++;
    }
}

void ft_hook(mlx_key_data_t key,void* param)
{
    t_shared_data *data = param;
    t_p_pos pos = data->p_pos;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
    if (key.key == MLX_KEY_UP && key.action == MLX_PRESS)
    {
        if (data->game_env->map && data->game_env->map[pos.y - 1] && data->game_env->map[pos.y - 1][pos.x] != '1')
        {
            printf ("up\n");
            data->game_env->map[pos.y][pos.x] = '0';
            data->game_env->map[pos.y - 1][pos.x] = 'N';
            data->p_pos = get_player_pos(data->game_env->map);
            rander_map(data->game_env, data->image);
        }
    }
    if (key.key == MLX_KEY_DOWN && key.action == MLX_PRESS)
    {
        if (data->game_env->map && data->game_env->map[pos.y - 1] && data->game_env->map[pos.y + 1][pos.x] != '1')
        {
            printf ("down\n");
            data->game_env->map[pos.y][pos.x] = '0';
            data->game_env->map[pos.y + 1][pos.x] = 'N';
            data->p_pos = get_player_pos(data->game_env->map);
            rander_map(data->game_env, data->image);
        }
    }
    if (key.key == MLX_KEY_RIGHT && key.action == MLX_PRESS)
    {
        if (data->game_env->map && data->game_env->map[pos.y] && data->game_env->map[pos.y][pos.x + 1] != '1')
        {
            printf ("right\n");
            data->game_env->map[pos.y][pos.x] = '0';
            data->game_env->map[pos.y][pos.x + 1] = 'N';
            data->p_pos = get_player_pos(data->game_env->map);
            rander_map(data->game_env, data->image);
        }
    }
    if (key.key == MLX_KEY_LEFT && key.action == MLX_PRESS)
    {
        if (data->game_env->map && data->game_env->map[pos.y] && data->game_env->map[pos.y][pos.x - 1] != '1')
        {
            printf ("left\n");
            data->game_env->map[pos.y][pos.x] = '0';
            data->game_env->map[pos.y][pos.x - 1] = 'N';
            data->p_pos = get_player_pos(data->game_env->map);
            rander_map(data->game_env, data->image);
        }
    }
}

int raycaster(t_game_env *game_env)
{
    t_shared_data data;
    data.game_env = game_env;
    data.p_pos =  get_player_pos(data.game_env->map);
    data.mlx = NULL;
    data.image = NULL;
    if (!(data.mlx = mlx_init(5120, 2880, "Cub3d", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(data.image = mlx_new_image(data.mlx, 5120, 2880)))
	{
		mlx_close_window(data.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(data.mlx, data.image, 0, 0) == -1)
	{
		mlx_close_window(data.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
    rander_map(data.game_env, data.image);
    mlx_key_hook(data.mlx, ft_hook, &data);
    mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
    return 0;
}
