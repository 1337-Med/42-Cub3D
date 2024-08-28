/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:05:54 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/08/28 15:01:25 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
#include "math.h"
# include "stdio.h"
# include "fcntl.h"
# include "../MLX42/include/MLX42/MLX42.h"

#define COLOR_NORTH 0xF5F5F5FF// Example color for north wall
#define COLOR_SOUTH 0xF5F5F5FF // Example color for south wall
#define COLOR_EAST  0xB5B5B5FF // Example color for east wall
#define COLOR_WEST  0xB5B5B5FF // Example color for west wall


typedef struct s_wall
{
	mlx_texture_t* north;
	mlx_texture_t* south;
	mlx_texture_t* west;
	mlx_texture_t* east;
} t_wall;

typedef struct s_side
{
	mlx_image_t* north;
	mlx_image_t* south;
	mlx_image_t* west;
	mlx_image_t* east;
} t_side;

#define MINI_FACTOR 0.2
#define WALL_WIDTH 1
#define PI 3.14159265358979323846
// #define NUM_RAYS 320
# define FOV (60 * (PI / 180))
# define WIDTH 920
# define HEIGHT 800
# define NUM_RAYS (WIDTH / WALL_WIDTH)
typedef struct s_game_env
{
	char	**map;
	t_wall	*wall;
	t_side	*side;
	int		floor;
	int		ceiling;

}	t_game_env;

// parsing functions
t_game_env *parser(int ac, char **av);
int get_rgba(int r, int g, int b, t_wall *wall);
void save_earth_sky(char **arr, t_game_env **game_env);
void save_walls(char **arr, t_game_env **game_env);
void free_print(char *s, t_wall *wall);
void check_map(char **map, t_wall *wall);
char **spliter(char *line);
void save_tools(char **arr, t_game_env **game_env);
void free_texture(t_wall *wall);
//general functions
t_game_env *parser(int ac, char **av);
int raycaster(t_game_env *game_env);


typedef struct s_p_pos
{
	float x;
	float y;
} t_p_pos;

typedef struct s_player
{
	t_p_pos pos;
	float raduis;
	float turn_dir;
	float walk_dir;
	float rota_angle;
	float move_speed;
	float rotate_speed;
} t_player;

typedef struct s_ray
{
	float horiz_x;
	float horiz_y;
	t_p_pos ray_p;
	float vert_x;
	float vert_y;
	float wall_hit_x;
	float wall_hit_y;
	float angle;
	float distance;
	int columnd_id;
	bool ray_up;
	bool ray_down;
	bool ray_right;
	bool ray_left;
} t_rays;
typedef struct s_shared_data
{
	t_game_env *game_env;
	mlx_t *mlx;
	mlx_image_t* image;
	t_p_pos p_pos;
	t_p_pos real_pos;
	t_player player;
	t_rays *rays;
	mlx_image_t* target_img;
} t_shared_data;
t_p_pos get_player_pos(char **map);
void texture_to_img(t_shared_data * data);
void rander_textures(t_shared_data *data, int i, int wall_top, int wall_bottom);
int degree_to_raidian(float dg);
# endif