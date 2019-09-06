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

t_vec_d		get_screen_coord(int x, int y)
{
	t_vec_d    d;

	d.x = (double)((double)x * 1.0 / (double)W);
	d.y = (double)((double)y * 1.0 / (double)H);
	d.z = 1;
	return (d);
}

t_vec_d		ray_hit_sphere(t_vec_d or, t_vec_d dir, t_sphere *sphere)
{
	t_vec_d    t;
	t_vec_d    k;
	
	t_vec_d C = sphere->center;
	double r = sphere->radius;
	t_vec_d oc = or - C;

	k.x = dot(dir, dir);
	k.y = 2*dot(oc, dir);
	k.z = dot(oc, oc) - r*r;

	double discriminant = k.y * k.y - 4 * k.x * k.z;
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

int		do_ray_trace(t_calc cl, t_rtv *rtv)
{
	t_sphere *closest_sphere = NULL;
	t_light		*light = rtv->lights;
	t_sphere	*head = rtv->spheres;

	calc_init(cl.or, cl.dir, &(rtv->calc));
	clos_intersection(to_calc(cl.or, cl.dir, cl.t_min, cl.t_max), &(rtv->calc), rtv);
	if (rtv->calc.clost_spher == NULL)
		return (0xFFCACB); //easy pink

	t_vec_d point = cl.or + multiplay(rtv->calc.clost_t, cl.dir);
	t_vec_d	normal = point - rtv->calc.clost_spher->center;
	// normal = multiplay( 1.0 / length(normal), normal);
	rtv->calc.point = point;

	normal = calc_normal(rtv, rtv->calc.clost_spher->obj_type);
	
	t_vec_d view = -1 * cl.dir;
	rtv->calc.norml = normal;
	rtv->calc.dir *= -1;
	t_vec_d color = calc_lightning(rtv, point, rtv->calc.clost_spher->specular) * rtv->calc.clost_spher->color;
	check_correct_chanels(&color);
	return (((int)(color.x) << 16) | ((int)(color.y) << 8 | (int)(color.z)));
}

void	main_cycle(t_rtv *rtv)
{
	int y;
	int x;

	x = -W / 2 - 1;
	t_vec_d or = (t_vec_d){0, 0, 0};

	while (x++ < W / 2 - 1)
	{
		y = -H / 2 - 1;
		while (y++ < H / 2 - 1)
		{
			t_vec_d dir = get_screen_coord(x, y);
			int color = do_ray_trace(to_calc(or, dir, 1, INFINIT), rtv);
			set_pixel(rtv->graph, x, y, color);
		}
	}
}

int			interactive_elem(t_rtv *rtv)
{
	t_graph		*g;

	g = rtv->graph;
	SDL_PollEvent(&g->event);
	if ((SDL_QUIT == g->event.type) || (SDL_KEYDOWN == g->event.type &&
	SDL_SCANCODE_ESCAPE == g->event.key.keysym.scancode))
		return (-1);
	return (0);
}

int		main(int ac, char **av)
{
	t_graph		graph;
	t_sphere	*st;
	t_sphere	*st2;
	t_sphere	*st3;
	t_light		*light;
	t_rtv		rtv;

	st = (t_sphere*)malloc(sizeof(t_sphere));
	st2 = (t_sphere*)malloc(sizeof(t_sphere));
	st3 = (t_sphere*)malloc(sizeof(t_sphere));

	rtv.graph = &graph;
	rtv.scenes_file = av[1];

	init_sdl(&graph);
	// rtv_init(&rtv, av[1]);
	// sdl_init(&rtv, (rtv.graph));

	// read_scene
		// rtv.lights = get_lights();
		// rtv.spheres = get_spheres();
	
	char *fig = "SPHERE; 2, 2, 1; 1.5; 200, 220, 200; 0, 1, 0; 500; 0.4";
	char *fig2 = "PLANE; 4, 2, 1; 1.5; 200, 220, 200; 0, 1, 0; 500; 0.4";
	char *lig = "AMBIENT; 0.2; 1, 4, 4; 2, 3, 4;";
	
	rtv.lights = NULL;
	rtv.spheres = NULL;

	read_scene(&rtv);

	main_cycle(&rtv);
	while (1)
	{	
		//ft_events(&graph);
		if (interactive_elem(&rtv) == -1)
		{
			SDL_Quit();
			exit(0);
		}
		SDL_UpdateWindowSurface(graph.win);
	}
	return (0);
}
