/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenyahy <nbenyahy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:05:54 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/08/12 21:45:43 by nbenyahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "stdio.h"
# include "fcntl.h"
# include "../MLX42/include/MLX42/MLX42.h"

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

// parsing functions
t_game_env *parser(int ac, char **av);
int get_rgba(int r, int g, int b, int a);
void save_earth_sky(char **arr, t_game_env **game_env);
void save_walls(char **arr, t_game_env **game_env);
void free_print(char *s);
void check_map(char **map);
char **spliter(char *line);
void save_tools(char **arr, t_game_env **game_env);

#define PI 3.14159265358979323846
#define NUM_RAYS 320


# endif