/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 17:42:26 by dshereme          #+#    #+#             */
/*   Updated: 2019/08/20 17:42:27 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	main_cycle(t_rtv *rtv)
{
	rtv->scene.O = (t_vec_d){0, 0, 0};
	int		x, y = -1;
	int		color = 0;
	while (++x < rtv->scr_w / 2)
	{
		y = -1;
		while (++y < rtv->scr_h / 2)
		{
			rtv->scene.D = CanvasToViewport(x, y);
			color = RayTrace(rtv->scene.O, rtv->scene.D, START_CANVAS, INFINIT);
			PutPixel(x, y, color);
		}
	}
}

t_vec_d		CanvasToViewport(t_rtv *rtv, int x, int y)
{
	return ((t_vec_d){(double)((double)x * 1.0 / (double)rtv->scr_w),
	(double)((double)y * 1.0 / (double)rtv->scr_h), (double)1});
	
}

int			TraceRay(t_rtv *rtv, int t_min, int t_max)
{
	double		closst_t = INFINIT;
	t_sphere 	*closst_sphere;
	t_vec_d		t;
	t_sphere	sphere;

	int			idx = 0;
	while (rtv->spheres[idx])
	{
		t = IntersectRaySphere(rtv, sphere);
		if (t.x >= t_min && t.x <= t_max && t.x < closst_t)
        {
            closst_t = t.x;
            closst_sphere = rtv->spheres[idx];
			break ;
        }
        if (t.y >= t_min && t.y <= t_max && t.y < closst_t)
        {
            closst_t = t.y;
            closst_sphere = rtv->spheres[idx];
			break ;
		}
		idx++;
	}
	if (closst_sphere == NULL)
        return (0x000000);
    return (((int)(closst_sphere->color.x) << 16) | ((int)(closst_sphere->color.y) << 8 | (int)(closst_sphere->color.z)));
}

t_vec_d		IntersectRaySphere(t_rtv *rtv, t_sphere *sphere)
{
	t_vec_d		t;
    t_vec_d		k;
    
    t_vec_d C = sphere->center;
    double r = sphere->radius;
    t_vec_d oc = rtv->scene.O - C;

    k.x = dot(rtv->scene.D, rtv->scene.D);
    k.y = 2*dot(oc, rtv->scene.D);
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

void            ft_events(t_graph *sdl)
{

    if (SDL_PollEvent(&sdl->event) && (sdl->event.type == SDL_QUIT ||
        sdl->event.key.keysym.sym == SDLK_ESCAPE))
        exit(0);
}

int		main(void)
{
	t_rtv *rtv = (t_rtv*)malloc(sizeof(t_rtv));
	rtv->spheres = (t_sphere**)malloc(sizeof(t_sphere*) * 3);
	t_sphere *sphere1 = (t_sphere*)malloc(sizeof(t_sphere));
	t_sphere *sphere2 = (t_sphere*)malloc(sizeof(t_sphere));
	rtv->spheres[0] = sphere1;
	rtv->spheres[1] = sphere2;
	
	sphere1->center = (t_vec_d){0, 1, 3};
	sphere1->radius = 1;
	sphere1->color = (t_vec_d){150, 150, 1};
	
	sphere2->center = (t_vec_d){0, 1, 3};
	sphere2->radius = 1;
	sphere2->color = (t_vec_d){100, 50, 1};
	
	rtv->spheres[2] = NULL;
	while (1)
	{
		main_cycle(rtv);
		 ft_events(rtv->graph)
		 SDL_Delay(10);
        SDL_UpdateWindowSurface(sdl.win);
	}
	return (0);
}
