/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 16:50:38 by dshereme          #+#    #+#             */
/*   Updated: 2019/08/18 16:50:41 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	put_color(t_rtv *rtv, int x, int y, int color)
{
	x = rtv->scr_w / 2 + x;
	y = rtv->scr_h / 2 - 1 - y;
	if (x < 0 || x >= rtv->scr_w  || y < 0 || y >= rtv->scr_h)
		return ;
	rtv->graph->pixs[x + y * rtv->scr_w] = color;
}

void	calc_scene(t_rtv *rtv)
{
	int		x, y = -1;
	int		color;
	rtv->scene.cam_pos = (t_vec_d){0, 0, 0};
	while (x >= -rtv->scr_w / 2 && x <= rtv->scr_w / 2)
	{
		while (y >= -rtv->scr_h / 2 && y <= rtv->scr_h / 2)
		{
			rtv->scene.cam_ray = canvas_to_viewport(x, y);
			color = ray_trace(rtv, START_CANVAS, INFINIT);
			put_color(rtv, x, y, color);
		}
	}
}

t_vec_d	CanvasToViewport(t_rtv *rtv, int x, int y)
{
	t_vec_d	vec;
	return ((t_vec_d){x * (double)Vw/rtv->scr_w, y * (double)Vh / rtv->scr_h, (double)START_CANVAS});
}

void	draw_scene(t_rtv *rtv)
{
	calc_scene(rtv);
	SDL_UpdateTexture(rtv->graph->texture, NULL,
	rtv->graph->pixs, rtv->scr_w * 4);
	SDL_RenderCopy(rtv->graph->render, rtv->graph->texture, NULL, NULL);
	SDL_RenderPresent(rtv->graph->render);
}

double            dot(t_vec_d v1, t_vec_d v2)
{
	return (v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2]);
}

t_vec_d	intersect_ray_sphere(t_scene s, t_sphere *sphere)
{
	t_vec_d	k;
	t_vec_d	t;

	t_vec_d	C = sphere->center;
	double	r = sphere->radius;
	t_vec_d	oc = s.cam_pos - C;
	k.x = dot(s.cam_ray, s.cam_ray);
	k.y = 2 * dot (oc, s.cam_ray);
	k.z = dot(oc, oc) * r * r;

	double discriminant =  k.y * k.y - 4 * k.x * k.z;
	if (discriminant < 0)
	{
		t.x = INFINIT;
		t.y = INFINIT;
		return (t);
	}
	t.x = (-k.y + sqrt(discriminant)) / (2 * k.x);
	t.y = (-k.y - sqrt(discriminant)) / (2 * k.x);
    return (t);
}



int		ray_trace(t_rtv *rtv, int t_min, int t_max)
{
	double		closest_t = INFINIT;
	t_sphere	*closest_sphere = NULL;
	t_sphere	*sphere = rtv->spheres;
	t_vec_d		t;

	while (sphere)
	{
		t = intersect_ray_sphere(rtv->scene.cam_pos, rtv->scene.cam_dir, rtv->spheres);
		if ((t.x >= t_min && t.x <= t_max) && t.x < closest_t)
		{
			closest_t = t.x;
			closest_sphere = sphere;
		}
		if ((t.y >= t_min && t.y <= t_max)&& t.y < closest_t)
		{
			closest_t = t.y;
			closest_sphere = sphere;
		}
		sphere = sphere->next;
	}
	return (closest_sphere == NULL ? 0x000000 : closest_sphere->color);
}
