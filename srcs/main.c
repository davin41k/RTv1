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
