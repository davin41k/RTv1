/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_func_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:00:59 by dshereme          #+#    #+#             */
/*   Updated: 2019/08/20 14:01:01 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

// void    init(t_object *obj)
// {
//     obj->center = (t_v){0, -1, 3};
//     obj->r = 1;
//     obj->color = (t_v){255, 0, 0};
// }

double		dot(t_vec_d v1, t_vec_d v2)
{
 return (v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2]);
}

void		init_sdl(t_graph *sdl)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	sdl->win = SDL_CreateWindow("RTv1",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, 0);
	if (NULL == sdl->win)
		exit(1);
	sdl->surface_window = SDL_GetWindowSurface(sdl->win);
	sdl->pixels2 = sdl->surface_window->pixels;
}

void		set_pixel(t_graph *img, int x, int y, int color)
{
	int    tmpx;
	int    tmpy;

	tmpx = W / 2 + x;
	tmpy = H / 2 - y - 1;
	if (tmpx < 0 || tmpx > (int)W || tmpy < 0 || tmpy > (int)H)
		return ;
	img->pixels2[tmpx + tmpy * W] = color;
}

t_vec_d		CanvasToViewport(int x, int y)
{
	t_vec_d    d;

	d.x = (double)((double)x * 1.0 / (double)W);
	d.y = (double)((double)y * 1.0 / (double)H);
	d.z = 1;
	return (d);
}

t_vec_d		IntersectRaySphere(t_vec_d O, t_vec_d D, t_sphere *sphere)
{
	t_vec_d    t;
	t_vec_d    k;
	
	t_vec_d C = sphere->center;
	double r = sphere->radius;
	t_vec_d oc = O - C;

	k.x = dot(D, D);
	k.y = 2*dot(oc, D);
	k.z = dot(oc, oc) - r*r;

	double discriminant = k.y * k.y - 4 * k.x * k.z;
	if (discriminant < 0)
	{
		t.x = 99999999999;
		t.y = 99999999999;
		return (t);
	}
	t.x = (-k.y + sqrt(discriminant)) / (2 * k.x);
	t.y = (-k.y - sqrt(discriminant)) / (2 * k.x);
	return (t);
}

int		TraceRay(t_vec_d O, t_vec_d D, int t_min, double t_max, t_rtv *rtv)
{
	double closest_t = 999999999;
	t_sphere *closest_sphere = NULL;
	t_light		*light = rtv->lights;
	// light.pos = (t_vec_d){2, 1, 0};
	// light.dir = (t_vec_d){1, 4, 4};
	t_sphere	*head = rtv->spheres;
	while (head)
	{
		t_vec_d t  = IntersectRaySphere(O, D, head);
		if (t.x >= t_min && t.x <= t_max && t.x < closest_t)
		{
			closest_t = t.x;
			closest_sphere = head;
		}
		//printf("HELLO\n");
		if (t.y >= t_min && t.y <= t_max && t.y < closest_t)
		{
			closest_t = t.y;
			closest_sphere = head;
		}
		head = head->next;
	}
	if (closest_sphere == NULL)
		return (0xFFCACB);

	t_vec_d point = O + multiplay(closest_t, D);
	t_vec_d	normal = point - closest_sphere->center;
	normal = multiplay( 1.0 / length(normal), normal);
//	int color = ((int)(closest_sphere->color.x) << 16) | ((int)(closest_sphere->color.y) << 8
//| (int)(closest_sphere->color.z));
	t_vec_d color = multiplay(ComputeLighting(light, point, normal, D), closest_sphere->color);
	
	int i = ((int)(color.x) << 16) | ((int)(color.y) << 8 | (int)(color.z));
	//printf("Color:\t%d\n", i);
	return (((int)(color.x) << 16) | ((int)(color.y) << 8 | (int)(color.z)));
	// return (color);
}

void	cycle(t_rtv *rtv)
{
	// t_vec_d     m;
	int y;
	int x;

	x = -W / 2;
	t_vec_d O = (t_vec_d){0, 0, 0};
	while (x++ < W / 2)
	{
		y = -H / 2;
		while (y++ < H / 2)
		{
			t_vec_d d = CanvasToViewport(x, y);
			int color = TraceRay(O, d, 1, 999999999, rtv);
			set_pixel(rtv->graph, x, y, color);
		}
	}
}

void	ft_events(t_graph *sdl)
{

	if (SDL_PollEvent(&sdl->event) && (sdl->event.type == SDL_QUIT ||
		sdl->event.key.keysym.sym == SDLK_ESCAPE))
		{
			SDL_Quit();
			exit(0);
		}
}

int		main(int ac, char **av)
{
	t_graph sdl;
	t_sphere *st;
	t_sphere *st2;
	t_sphere *st3;
	t_rtv	rtv;

	st = (t_sphere*)malloc(sizeof(t_sphere));
	st2 = (t_sphere*)malloc(sizeof(t_sphere));
	st3 = (t_sphere*)malloc(sizeof(t_sphere));
	init_sdl(&sdl);

	rtv.lights = get_lights();
	rtv.spheres = get_spheres();;
	rtv.graph = &sdl;
	
	st->center = (t_vec_d){0, 0, 3};
	st->radius = 1;
	st->color = (t_vec_d){150, 150, 1};
	while (1)
	{
		cycle(&rtv);
		ft_events(&sdl);
		SDL_Delay(10);
		SDL_UpdateWindowSurface(sdl.win);
	}
	return (0);
}
