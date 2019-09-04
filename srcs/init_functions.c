/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 18:57:45 by dshereme          #+#    #+#             */
/*   Updated: 2019/08/15 18:57:48 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rtv1.h"


void    sdl_init(t_rtv *rtv, t_graph *graph)
{
	if ((SDL_Init(SDL_INIT_VIDEO) != 0))
		error_exit(MEM_ERR);
	graph->win = SDL_CreateWindow("RTv1", 250,
	250, W, H, SDL_WINDOW_SHOWN);
	if (graph->win == NULL)
		error_exit(MEM_ERR);
	graph->render = SDL_CreateRenderer(graph->win, -1,
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (graph->render == NULL)
		error_exit(MEM_ERR);
	graph->texture = SDL_CreateTexture(graph->render,
	SDL_PIXELFORMAT_ARGB8888,
	SDL_TEXTUREACCESS_STREAMING, rtv->scr_w, rtv->scr_h);
	if (!(graph->surface_window = SDL_GetWindowSurface(graph->win)))
		error_exit(MEM_ERR);
	printf("SDSDSDDS\n");
	graph->pixels2 = graph->surface_window->pixels;

}

int		rtv_init(t_rtv *rtv, char *scene_file_name)
{
	rtv->scr_w = WIN_HD_WIDTH;
	rtv->scr_h = WIN_HD_HEIGHT;
	rtv->scenes_file = scene_file_name;
	if (!(rtv->graph = (t_graph*)ft_memalloc(sizeof(t_graph))))
		error_exit(MEM_ERR);
	return (1);
}