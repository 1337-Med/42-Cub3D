/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejdoub <amejdoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 13:05:54 by nbenyahy          #+#    #+#             */
/*   Updated: 2024/11/01 11:54:41 by amejdoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include "libft.h"
# include <math.h>

typedef struct s_wall
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
}					t_wall;

typedef struct s_side
{
	mlx_image_t		*north;
	mlx_image_t		*south;
	mlx_image_t		*west;
	mlx_image_t		*east;
}				t_side;
// FOV = (60 * (PI / 180))
// NUM_RAYS = WIDTH

# define MINI_FACTOR 0.4
# define TAIL_SIZE 32
# define PI 3.14159265358979323846
# define FOV 1.04719755
# define WIDTH 920
# define HEIGHT 800
# define NUM_RAYS WIDTH

typedef struct s_game_env
{
	char			**map;
	char			dir;
	t_wall			*wall;
	t_side			*side;
	int				floor;
	int				ceiling;
	int				floor_status;
	int				ceiling_status;

}					t_game_env;

// parsing functions
void				skip_spaces(int *i, char *s);
int					check_empty_line(char *line);
t_game_env			*parser(int ac, char **av);
int					get_rgba(int r, int g, int b, t_wall *wall);
void				save_earth_sky(char **arr, t_game_env **game_env);
void				save_walls(char **arr, t_game_env **game_env);
void				free_print(char *s, t_wall *wall);
void				check_map(t_game_env *game_env);
char				**spliter(char *line);
void				save_tools(char **arr, t_game_env **game_env);
void				free_texture(t_wall *wall);
// general functions
t_game_env			*parser(int ac, char **av);
int					raycaster(t_game_env *game_env);

typedef struct s_p_pos
{
	float			x;
	float			y;
}					t_p_pos;

typedef struct s_player
{
	float			raduis;
	float			turn_dir;
	float			walk_dir;
	float			rota_angle;
	float			move_speed;
	float			rotate_speed;
}					t_player;

typedef struct s_cord
{
	int				x;
	int				y;
}					t_cord;

typedef struct s_ray
{
	float			horiz_x;
	float			horiz_y;
	t_p_pos			ray_p;
	float			vert_x;
	float			vert_y;
	float			wall_hit_x;
	float			wall_hit_y;
	float			angle;
	float			distance;
	int				columnd_id;
	bool			ray_up;
	bool			ray_down;
	bool			ray_right;
	bool			ray_left;
}					t_rays;
typedef struct s_shared_data
{
	t_game_env		*game_env;
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_p_pos			p_pos;
	t_p_pos			real_pos;
	t_player		player;
	t_rays			*rays;
	mlx_image_t		*target_img;
}					t_shared_data;
t_p_pos				get_player_pos(char **map);
void				texture_to_img(t_shared_data *data);
void				rander_textures(t_shared_data *data, int i, int wall_top,
						int wall_bottom);
int					degree_to_raidian(float dg);
void				get_horizontal_inter(t_shared_data *data, int i);
void				get_vertical_inter(t_shared_data *data, int i);
bool				wall_found(t_shared_data *data, t_cord map, int i,
						t_p_pos inter);
void				ft_hook(void *param);
bool				move_up_condition(t_shared_data *data);
void				render_map(t_shared_data *data);
float				norm_angle(float angle);
void				create_rays(t_shared_data *data);
void				init_ray(t_shared_data *data, int i, float ray_angle);
void				cast_rays(t_shared_data *data, int num_rays);
void				smaller_distance(t_shared_data *data, int i, float horz,
						float vertical);
void				choose_smaller(t_shared_data *data, int i, char c,
						float chosen);
float				distance_two_p(float x1, float y1, float x2, float y2);
void				render_rec(int y, int x, mlx_image_t *image, char c);
void				ft_loop(void *data);
void				movement_d(t_shared_data *data);
void				movement_a(t_shared_data *data);
void				walkturn_dir(t_shared_data *data);
void				calcul_new_cord(t_shared_data *data);
#endif