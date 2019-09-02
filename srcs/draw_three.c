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

int		TraceRay(t_vec_d O, t_vec_d D, double t_min, double t_max, t_rtv *rtv)
{
	t_sphere *closest_sphere = NULL;
	t_light		*light = rtv->lights;
	t_sphere	*head = rtv->spheres;

	calc_init(O, D, &(rtv->calc));
	ClosestIntersection(O, D, t_min, t_max, &(rtv->calc), rtv);
	if (rtv->calc.clost_spher == NULL)
		return (0xFFCACB); //easy pink

	t_vec_d point = O + multiplay(rtv->calc.clost_t, D);
	t_vec_d	normal = point - rtv->calc.clost_spher->center;
	// normal = multiplay( 1.0 / length(normal), normal);
	rtv->calc.point = point;

	normal = calc_normal(rtv, rtv->calc.clost_spher->obj_type);
	
	t_vec_d view = -1 * D;
	rtv->calc.N = normal;
	rtv->calc.D *= -1;
	t_vec_d color = ComputeLighting(rtv, point, rtv->calc.clost_spher->specular) * rtv->calc.clost_spher->color;
	check_correct_chanels(&color);
	return (((int)(color.x) << 16) | ((int)(color.y) << 8 | (int)(color.z)));
}

void	cycle(t_rtv *rtv)
{
	// t_vec_d     m;
	int y;
	int x;

	x = -W / 2 - 1;													// - 1
	t_vec_d O = (t_vec_d){0, 0, 0};

	while (x++ < W / 2 - 1)
	{
		y = -H / 2 - 1;											// поставил -1
		while (y++ < H / 2 - 1)
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
	t_graph		sdl;
	t_sphere	*st;
	t_sphere	*st2;
	t_sphere	*st3;
	t_light		*light;
	t_rtv		rtv;

	st = (t_sphere*)malloc(sizeof(t_sphere));
	st2 = (t_sphere*)malloc(sizeof(t_sphere));
	st3 = (t_sphere*)malloc(sizeof(t_sphere));
	init_sdl(&sdl);
	rtv.graph = &sdl;
	
	
	char *fig = "SPHERE; 2, 2, 1; 1.5; 200, 220, 200; 0, 1, 0; 500; 0.4";
	char *fig2 = "PLANE; 4, 2, 1; 1.5; 200, 220, 200; 0, 1, 0; 500; 0.4";
	char *lig = "AMBIENT; 0.2; 1, 4, 4; 2, 3, 4;";
	//st = get_sphere(fig);
	//rtv.spheres = st;
	// light = create_light(lig);
	// printf("---------------------------------------------------------\n");
	// print_light(light);
	// printf("---------------------------------------------------------\n");
	// print_object(st);
	// printf("%s\n", fig);
	
	rtv.lights = NULL;
	rtv.spheres = NULL;
	// get_object(fig, &rtv);
	// get_object(fig2, &rtv);
	// get_object(lig, &rtv);
	// print_all_objects(&rtv);

	rtv.scenes_file = av[1];
	read_scene(&rtv);
	// printf("---------------------------------------------------------\n");	
	//print_all_objects(&rtv);
	// printf("---------------------------------------------------------\n");

	cycle(&rtv);
	while (1)
	{	
		ft_events(&sdl);
		//SDL_Delay(1000);
		SDL_UpdateWindowSurface(sdl.win);
	}
	return (0);
}
