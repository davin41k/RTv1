/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 16:36:35 by dshereme          #+#    #+#             */
/*   Updated: 2019/08/15 16:37:50 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H

# define RTV1_H

# define WIN_FHD_HEIGHT 1080
# define WIN_FHD_WIDTH	1080
# define WIN_HD_HEIGHT	720
# define WIN_HD_WIDTH	1280

# define GET_NUM		0
# define INCREASE		1
# define ON				1
# define OFF			0

# define USAGE			0
# define THREAD_ERR		1
# define MEM_ERR		2
# define SCENE_ERR		3
# define INCORRECT_MAP	4
# define LOAD_ERR		5
# define FORMAT_ERR		6

# define _USE_MATH_DEFINES

# define INFINIT		1000000000
# define EPSILON		0.0001
# define START_CANVAS	1
# define Vw				1
# define Vh				1

# define W				1000
# define H				1000

# define AMBIENT		4
# define POINT			5
# define DIRECTIONAL	6

# define CAMERA			7

# define PLANE			0
# define SPHERE			1
# define CONE			2
# define CYLINDER		3

# define FIGURE			0
# define LIGHT			1

# define NO_NUMBER		-1

# define EMPTY_LINE		0

# define MAP_FORMAT		"rtv1"

# include <mlx.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <float.h>
# include "libft.h"
# include "get_next_line.h"
//DBL_MAX
# include "SDL.h"


typedef	double	t_vec_d	__attribute__((__ext_vector_type__(3)));
typedef	int		t_vec_i	__attribute__((__ext_vector_type__(3)));

typedef	struct		s_sphere	t_sphere;
typedef	struct		s_light		t_light;

typedef	struct		s_point 
{
	int				x;
	int				y;
	int				z;
}					t_point;

typedef	struct		s_graph
{
	SDL_Window		*win;
	SDL_Renderer	*render;
	SDL_Event		event;
	SDL_Texture		*texture;
	SDL_Surface		*surface_window;
	int				*pixs;
	int				*pixels2;
}					t_graph;

struct				s_sphere
{
	int				obj_type;
	t_vec_d			center;
	double			radius;
	t_vec_d			color;
	t_vec_d			rotation;
	int				specular;
	double			fig_angle;
	t_sphere		*next;
};		

typedef	struct		s_scene
{
	t_vec_d			O;
	t_vec_d			D;
	t_vec_d			cam_ray;
}					t_scene;

typedef	struct		s_light
{
	int				type;
	double			intensity;
	t_vec_d			pos;
	t_vec_d			dir;
	t_light			*next;
}					t_light;

typedef	struct		s_calc
{
	t_vec_d			or;
	t_vec_d			dir;
	t_vec_d			l_ray;
	t_vec_d			norml;
	double			t_min;
	double			t_max;
	double			clost_t;
	t_sphere		*clost_spher;
	t_vec_d			point;
	t_vec_d			normal;
	t_vec_d			view;
}					t_calc;

typedef	struct		s_rtv
{
	int				scr_h;
	int				scr_w;
	t_sphere		*spheres;
	t_calc			calc;
	t_scene			scene;
	char			*scenes_file;
	t_graph			*graph;
	t_light			*lights;
}					t_rtv;

//	***EXITS_FUNC***
int		escape_exit(int key);
int		red_exit(int key);
void	read_error(void);
void	error_exit(int errno);

//	***INIT_FUNCTIONS***
void    sdl_init(t_rtv *rtv, t_graph *graph);
int		rtv_init(t_rtv *rtv, char *scenes_file);

//	***DRAW_FUNC_TWO***
double	dot(t_vec_d v1, t_vec_d v2);
void	init_sdl(t_graph *sdl);
void	set_pixel(t_graph *img, int x, int y, int color);
t_vec_d	get_screen_coord(int x, int y);
t_vec_d	ray_hit_sphere(t_vec_d or, t_vec_d dir, t_sphere *sphere);
int		do_ray_trace(t_calc cl, t_rtv *rtv);
void	cycle(t_rtv *rtv);
void	t_events(t_graph *sdl);
int		main(int ac, char **av);

//	***LUGHTNING***
double	calc_lightning(t_rtv *rtv, t_vec_d P, int spec);
t_vec_d	multiplay(double k, t_vec_d vec);
double length(t_vec_d vec);
void	check_correct_chanels(t_vec_d *color);

//	***FIGURE_FACTORY***
t_light		*get_light(int type, double intensity, t_vec_d pos, t_vec_d dir);
t_light		*get_lights(void);
t_sphere	*create_sphere(t_vec_d center, double radius, t_vec_d color, int spec);
t_sphere	*get_spheres(void);

//	***MORE_DRAW_FUNC***
t_calc		to_calc(t_vec_d or, t_vec_d dir, double t_min, double t_max);
int			clos_intersection(t_calc c, t_calc *calc, t_rtv *rtv);
void		calc_init(t_vec_d or, t_vec_d dir, t_calc *calc);
t_vec_d		intersec_object(t_vec_d or, t_vec_d dir, t_sphere *obj);
t_vec_d		intersec_ray_plane(t_vec_d or, t_vec_d dir, t_sphere *plane);
t_vec_d		intersec_ray_cylinder(t_vec_d or, t_vec_d dir, t_sphere *cone);
t_vec_d		calc_normal(t_rtv *rtv, int fig_type);
t_vec_d		intersec_ray_cone(t_vec_d or, t_vec_d dir, t_sphere *cone);

//	***SCENE_READER***
int			read_scene(t_rtv *rtv);
t_sphere	*get_sphere(char *obj);
int			get_obj_type(char *object);
t_vec_d		get_next_vec(char **fig);
double		get_next_num(char **fig);
t_light		*create_light(char *obj);
int			check_map_format(char *file_name);
void		get_object(char *object, t_rtv *rtv);
void		nullify_object(t_sphere *obj);
void		nullify_light(t_light *light);
t_vec_d		get_next_vec(char **fig);
double		get_next_num(char **fig);
int			get_abstract_obj_type(char *obj);
int			shift_obj_type(char **fig);
t_vec_d		get_cam_pos(char *obj);

//	***HELP_FUNC***
void	print_object(t_sphere *sphere);
void	print_state(char *state, double value);
void	print_vec(char *state, t_vec_d vec);
void	print_light(t_light *light);
void	print_all_objects(t_rtv *rtv);
//to libf
double		ft_atof(char *nptr);

void    sdl_init(t_rtv *rtv, t_graph *graph);
int		rtv_init(t_rtv *rtv, char *scene_file_name);


#endif
