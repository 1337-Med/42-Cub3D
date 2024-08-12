/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:05:54 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/08/12 21:01:29 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "stdio.h"
# include "fcntl.h"
# include "../MLX42/include/MLX42/MLX42.h"
// # include "../mlx/include/MLX42/MLX42.h"

typedef struct s_wall
{
	mlx_texture_t* north;
	mlx_texture_t* south;
	mlx_texture_t* west;
	mlx_texture_t* east;
} t_wall;

typedef struct s_game_env
{
	char	**map;
	t_wall	*wall;
	int		floor;
	int		ceiling;

}	t_game_env;
t_game_env *parser(int ac, char **av);
int raycaster(t_game_env *game_env);
#define PI 3.14159265358979323846
#define NUM_RAYS 320

typedef struct s_p_pos
{
	int x;
	int y;
} t_p_pos;

typedef struct s_shared_data
{
	t_game_env *game_env;
	mlx_t *mlx;
	mlx_image_t* image;
	t_p_pos p_pos;
	t_p_pos real_pos;
} t_shared_data;
t_p_pos get_player_pos(char **map);
# endif