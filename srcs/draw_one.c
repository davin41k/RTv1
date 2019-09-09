/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 18:46:22 by dshereme          #+#    #+#             */
/*   Updated: 2019/09/08 18:46:24 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		dot(t_vec_d v1, t_vec_d v2)
{
	return (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]);
}

t_vec_d		ray_hit_sphere(t_vec_d or, t_vec_d dir, t_sphere *sphere)
{
	t_vec_d		x;
	t_vec_d		k;
	t_vec_d		c;
	double		rad;
	double		discriminant;

	c = sphere->center;
	rad = sphere->radius;
	k.x = dot(dir, dir);
	k.y = 2 * dot((or - c), dir);
	k.z = dot((or - c), (or - c)) - pow(rad, 2);
	discriminant = k.y * k.y - 4 * k.x * k.z;
	if (discriminant < 0)
	{
		x.x = INFINIT;
		x.y = INFINIT;
		return (x);
	}
	x.x = (-k.y + sqrt(discriminant)) / (2 * k.x);
	x.y = (-k.y - sqrt(discriminant)) / (2 * k.x);
	return (x);
}

int		do_ray_trace(t_calc cl, t_rtv *rtv)
{
	t_light		*light;
	t_sphere	*head;
	t_vec_d		point;
	t_vec_d		normal;

	light = rtv->lights;
	head = rtv->spheres;
	calc_init(cl.or, cl.dir, &(rtv->calc));
	clos_intersection(to_calc(cl.or, cl.dir, cl.t_min, cl.t_max),
	&(rtv->calc), rtv);
	if (rtv->calc.clost_spher == NULL)
		return (BG_COLOR);
	point = cl.or + multiplay(rtv->calc.clost_t, cl.dir);
	normal = point - rtv->calc.clost_spher->center;
	rtv->calc.point = point;
	normal = calc_normal(rtv, rtv->calc.clost_spher->obj_type);
	rtv->calc.norml = normal;
	rtv->calc.dir *= -1;
	rtv->calc.color = calc_lightning(rtv, point,
	rtv->calc.clost_spher->specular) * rtv->calc.clost_spher->color;
	check_correct_chanels(&rtv->calc.color);
	return (((int)(rtv->calc.color.x) << 16) | ((int)(rtv->calc.color.y)
	<< 8 | (int)(rtv->calc.color.z)));
}
