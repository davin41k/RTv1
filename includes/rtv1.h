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
# define MAP_ERR		3
# define INCORRECT_MAP	4
# define LOAD_ERR		5
# define FORMAT_ERR		6

# define _USE_MATH_DEFINES

# define INFINIT		1000000000
# define START_CANVAS	1
# define Vw				1
# define Vh				1

# define W				1000
# define H				1000

# define AMBIENT		0
# define POINT			1
# define DIRECTIONAL	2

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
// # include "libft.h"
// # include "get_next_line.h"
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
	t_vec_d			center;
	double			radius;
	t_vec_d			color;
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

typedef	struct		s_rtv
{
	int				scr_h;
	int				scr_w;
	t_sphere		*spheres;
	t_scene			scene;
	char			*map_file_name;
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
int		rtv_init(t_rtv *rtv, char *map_file_name);

//	***DRAW_FUNC_TWO***
double	dot(t_vec_d v1, t_vec_d v2);
void	init_sdl(t_graph *sdl);
void	set_pixel(t_graph *img, int x, int y, int color);
t_vec_d	CanvasToViewport(int x, int y);
t_vec_d	IntersectRaySphere(t_vec_d O, t_vec_d D, t_sphere *sphere);
int		TraceRay(t_vec_d O, t_vec_d D, int t_min, double t_max, t_rtv *rtv);
void	cycle(t_rtv *rtv);
void	t_events(t_graph *sdl);
int		main(int ac, char **av);

//	***LUGHTNING***
double	ComputeLighting(t_light *light, t_vec_d P, t_vec_d N, t_vec_d D);
t_vec_d	multiplay(double k, t_vec_d vec);
double length(t_vec_d vec);

//	***FIGURE_FACTORY***
t_light		*get_light(int type, double intensity, t_vec_d pos, t_vec_d dir);
t_light		*get_lights(void);
t_sphere	*create_sphere(t_vec_d center, double radius, t_vec_d color);
t_sphere	*get_spheres(void);

#endif
