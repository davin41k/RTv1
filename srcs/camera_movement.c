/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 19:59:02 by dshereme          #+#    #+#             */
/*   Updated: 2019/09/08 19:59:07 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	camera_rotate(t_rtv *rtv)
{
	t_graph		*g;
	t_calc		*c;
	double		tmp;

	g = rtv->graph;
	c = &rtv->calc;
	if (g->event.type == SDL_KEYDOWN)
	{
		tmp = c->dir.y;
		c->dir.y = tmp * cos(g->angle.x) + c->dir.z * sin(g->angle.x);
		c->dir.z = -(tmp) * sin(g->angle.x) + c->dir.z * cos(g->angle.x);
	}
}

void	change_angle(t_rtv *rtv)
{
	t_graph		*g;

	g = rtv->graph;
	if (g->event.type == SDL_KEYDOWN)
	{
		if (g->event.key.keysym.sym == SDLK_UP)
			g->angle += 0.24;
		else if (g->event.key.keysym.sym == SDLK_DOWN)
			g->angle -= 0.24;
	}
}
