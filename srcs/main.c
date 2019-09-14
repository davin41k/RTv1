/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 19:54:16 by dshereme          #+#    #+#             */
/*   Updated: 2019/08/15 19:54:17 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

// void	texture_mapping(t_rtv *rtv)
// {
// 	double	final_index2;
// 	t_vec_d	center = rtv->spheres->center;
// 	t_vec_d	point = rtv->calc.point;
// 	t_vec_d	normal = rtv->calc.normal;
// 	double	temp = acos(normal.z);
// 	double	temp2 = atan2(normal.y, normal.x);
// 	double	v = temp / PI;
// 	if (temp2 < 0)
// 		temp2 += (2 * PI);
// 	double u = temp2 / (2 * PI);
// 	int		width = u
// }

static	void	main_loop(t_rtv *rtv)
{
	int			is_running;

	is_running = 1;
	while (is_running)
	{
		if (interactive_elem(rtv) == -1)
		{
			SDL_Quit();
			is_running = 0;
		}
		SDL_UpdateWindowSurface(rtv->graph->win);
	}
}

void	show_texture(t_rtv *rtv)
{
	SDL_Surface *tex;
	int			i;
	int			j;
	int			*pixs;

	i = j = -1;

	tex = rtv->texture;
	pixs = (int*)tex->pixels;
	while (++i)
	{
		j = -1;
		while (++j)
		rtv->graph->pixs[i * j + j] = pixs[i * j + j];
	}
}

int				main(int ac, char **av)
{
	t_rtv		rtv;

	if (ac != 2)
		error_exit(USAGE);
	rtv_init(&rtv, av[1]);
	sdl_init(&rtv, rtv.graph);
	read_scene(&rtv);
	main_cycle(&rtv);
	main_loop(&rtv);
	return (0);
}
