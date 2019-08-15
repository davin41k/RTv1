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

# include <mlx.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include "libft.h"
# include "get_next_line.h"
# include "SDL.h"

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

}					t_graph;

typedef	struct		s_rtv
{
	int				scr_h;
	int				scr_w;
	char			*map_file_name;
	t_graph			*graph;
}					t_rtv;


#endif
