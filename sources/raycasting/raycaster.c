/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:19:40 by amejdoub          #+#    #+#             */
/*   Updated: 2024/08/14 11:20:31 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void DDA(int x1, int y1, int x2, int y2, mlx_image_t* image) {
    // Calculate dx and dy
    int dx = x2 - x1;
    int dy = y2 - y1;

    // Calculate the number of steps required for generating pixels
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    // Calculate the increment in x & y for each step
    float x_inc = dx / (float) steps;
    float y_inc = dy / (float) steps;

    // Initialize starting point
    float x = x1;
    float y = y1;

    // Put pixel at starting point
    mlx_put_pixel(image, round(x), round(y), 0xda000099);
    // putpixel(round(x), round(y), WHITE);

    // Generate points and plot them
    for (int i = 0; i < steps; i++) {
        x += x_inc;
        y += y_inc;
        mlx_put_pixel(image, round(x), round(y), 0xda000099);
    }
}
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

void render_player(t_shared_data *data)
{
    int color = 0xFFFFFFFF;
//     // printf ("p pos %d %d\n", data->real_pos., x);
    int i = -5;
int j = -5;

while (i <= 5)
{
    j = -5;
    while (j <= 5)
    {
        mlx_put_pixel(data->image, data->real_pos.x + j, data->real_pos.y + i, color);
        j++;
    }
    i++;
}

    // i = 0;
    // while (i < 5)
    // {
    //     j = 0;
    //     while (j < 5)
    //     {
    //         mlx_put_pixel(data->image, data->real_pos.x + j, data->real_pos.y + i, color);
    //         j++;
    //     }
    //     i++;
    // }
    // mlx_put_pixel(data->image, data->real_pos.x, data->real_pos.y, color);
    DDA(data->real_pos.x, data->real_pos.y, data->real_pos.x + cos(data->player.rota_angle) * 20, data->real_pos.y + sin(data->player.rota_angle) * 20, data->image);
    // int i = 0;
    // while (i < 5)
    // {
    //     mlx_put_pixel(image, x + i, y,  0xFF0000FF);
    //     i++;
    // }
}

void rander_map (t_shared_data *data)
{
    int x = 0;
    int y = 0;
    while (data->game_env->map[y])
    {
        x = 0;
        while (data->game_env->map[y][x])
        {
            if (data->game_env->map[y][x] == '1')
                render_rec(y, x, data->image, 'W');
            if (data->game_env->map[y][x] == '0' || data->game_env->map[y][x] == 'N')
            {
                render_rec(y, x, data->image, 'F');
            }
            x++;
        }
        y++;
    }
    render_player(data);
}

void ft_hook(mlx_key_data_t key,void* param)
{
    t_shared_data *data = param;
    // t_p_pos pos = data->p_pos;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
    if (key.key == MLX_KEY_RIGHT && key.action == MLX_RELEASE)
    {
        data->player.turn_dir = 0;
    }
    if (key.key == MLX_KEY_LEFT && key.action == MLX_RELEASE)
    {
        data->player.turn_dir = 0;
    }
    if (key.key == MLX_KEY_RIGHT && mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
    {
        data->player.turn_dir = 1;
    }
    if (key.key == MLX_KEY_LEFT && mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
    {
        data->player.turn_dir = -1;
    }
    if (key.key == MLX_KEY_S && key.action == MLX_RELEASE)
    {
        data->player.walk_dir = 0;
    }
    if (key.key == MLX_KEY_W && key.action == MLX_RELEASE)
    {
        data->player.walk_dir = 0;
    }
    if (key.key == MLX_KEY_W && mlx_is_key_down(data->mlx, MLX_KEY_W))
    {
        printf ("up\n");
        data->player.walk_dir = 1;
    }
    if (key.key == MLX_KEY_S && mlx_is_key_down(data->mlx, MLX_KEY_S))
    {
        data->player.walk_dir = -1;
    }
    int move_step = data->player.walk_dir * data->player.move_speed;
    int new_x =  data->real_pos.x + cos(data->player.rota_angle) * move_step; 
    int new_y = data->real_pos.y + sin(data->player.rota_angle) * move_step;
    if (data->game_env->map && data->game_env->map[new_y / 32] && data->game_env->map[new_y / 32][new_x / 32] != '1')
    {
        data->real_pos.x = new_x;
        data->real_pos.y = new_y;
        
    }
    printf("the walk dir is %d the turn dir is %d\n", data->player.walk_dir, data->player.turn_dir);
    printf("ROTATION ANGLE IS %.2f\n", data->player.rota_angle);
    data->player.rota_angle += data->player.turn_dir * data->player.rotate_speed;
    // if (key.key == MLX_KEY_D && key.action == MLX_PRESS)
    // {
    //     if (data->game_env->map && data->game_env->map[pos.y] && data->game_env->map[pos.y][pos.x + 1] != '1')
    //     {
    //         printf ("right\n");
    //         data->game_env->map[pos.y][pos.x] = '0';
    //         data->game_env->map[pos.y][pos.x + 1] = 'N';
    //         data->p_pos = get_player_pos(data->game_env->map);
    //         data->real_pos = get_player_pos(data->game_env->map);
    //         data->real_pos.x = (data->real_pos.x * 32) + 16;
    //         data->real_pos.y = (data->real_pos.y * 32) + 16;
    //         // rander_map(data);
    //     }
    // }
    // if (key.key == MLX_KEY_A && key.action == MLX_PRESS)
    // {
    //     if (data->game_env->map && data->game_env->map[pos.y] && data->game_env->map[pos.y][pos.x - 1] != '1')
    //     {
    //         printf ("left\n");
    //         data->game_env->map[pos.y][pos.x] = '0';
    //         data->game_env->map[pos.y][pos.x - 1] = 'N';
    //         data->p_pos = get_player_pos(data->game_env->map);
    //         data->real_pos = get_player_pos(data->game_env->map);
    //         data->real_pos.x = (data->real_pos.x * 32) + 16;
    //         data->real_pos.y = (data->real_pos.y * 32) + 16;
    //     }
    // }
    rander_map(data);
}

int raycaster(t_game_env *game_env)
{
    int i = 0;
    while (game_env->map[i])
    {
        printf("%s\n", game_env->map[i]);
        i++;
    }
    t_shared_data data;
    data.game_env = game_env;
    t_player player;
    data.p_pos =  get_player_pos(data.game_env->map);
    data.real_pos = get_player_pos(data.game_env->map);
    data.real_pos.x = (data.real_pos.x * 32) + 16;
    data.real_pos.y = (data.real_pos.y * 32) + 16;
    // printf("the position is %d %d\n", data.p_pos.y, data.p_pos.x);
    player.pos = data.real_pos;
    player.raduis = 3;
    player.walk_dir = 0;
    player.turn_dir = 0;
    player.rota_angle = PI / 2;
    player.move_speed = 4;
    player.rotate_speed = 4 * (PI / 180);
    data.player = player;
    // printf ("y is %d x is %d\n", data.real_pos.y, data.real_pos.x);
    // printf ("PREEEEV y is %d x is %d\n", (data.p_pos.y * 32) + 16, (data.p_pos.x * 32) + 16);
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
    rander_map(&data);
    mlx_key_hook(data.mlx, ft_hook, &data);
    mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
    return 0;
}
