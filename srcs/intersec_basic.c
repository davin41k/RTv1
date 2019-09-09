/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersec_basic.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 17:44:45 by dshereme          #+#    #+#             */
/*   Updated: 2019/09/08 17:44:47 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			cycle_logic(t_vec_d t, t_calc c, t_calc *calc, t_sphere *head)
{
	int		flag;

	flag = 0;
	if (t.x >= c.t_min && t.x <= c.t_max && t.x < calc->clost_t)
	{
		calc->clost_t = t.x;
		calc->clost_spher = head;
		flag = 1;
	}
	if (t.y >= c.t_min && t.y <= c.t_max && t.y < calc->clost_t)
	{
		calc->clost_t = t.y;
		calc->clost_spher = head;
		flag = 1;
	}
	return (flag);
}

int			clos_intersection(t_calc c, t_calc *calc, t_rtv *rtv)
{
	t_light		*light;
	t_sphere	*head;
	t_vec_d		t;
	int			flag;

	flag = 0;
	light = rtv->lights;
	head = rtv->spheres;
	calc->clost_t = INFINIT;
	calc->clost_spher = NULL;
	while (head)
	{
		t = intersec_object(c.or, c.dir, head);
		flag = cycle_logic(t, c, calc, head);
		head = head->next;
	}
	return (flag);
}

t_vec_d		calc_normal(t_rtv *rtv, int fig_type)
{
	t_vec_d		normal;
	double		tmp;

	if (fig_type == SPHERE)
	{
		normal = rtv->calc.point - rtv->calc.clost_spher->center;
		normal = multiplay(1.0 / length(normal), normal);
	}
	else if (fig_type == PLANE)
	// {	
	// 	normal = multiplay(1.0 / length(rtv->calc.clost_spher->rotation), rtv->calc.clost_spher->rotation);
	// }
		normal = (dot(rtv->calc.dir, rtv->calc.clost_spher->rotation) < 0.0 ?
		-rtv->calc.clost_spher->rotation : rtv->calc.clost_spher->rotation);
	else if (fig_type == CYLINDER || fig_type == CONE)
	{
		normal = 1.0 / length(rtv->calc.clost_spher->rotation) *
		rtv->calc.clost_spher->rotation;
		tmp = dot(rtv->calc.dir, normal) * rtv->calc.clost_t +
		dot((rtv->calc.or - rtv->calc.clost_spher->center), normal);
		normal = rtv->calc.point - rtv->calc.clost_spher->center -
		multiplay(tmp, normal);
	}
	return (normal);
}

t_vec_d		intersec_object(t_vec_d or, t_vec_d dir, t_sphere *obj)
{
	t_vec_d		t;

	if (obj->obj_type == SPHERE)
		t = ray_hit_sphere(or, dir, obj);
	else if (obj->obj_type == PLANE)
		t = intersec_ray_plane(or, dir, obj);
	else if (obj->obj_type == CYLINDER)
		t = intersec_ray_cylinder(or, dir, obj);
	else if (obj->obj_type == CONE)
		t = intersec_ray_cone(or, dir, obj);
	return (t);
}

t_vec_d		intersec_ray_plane(t_vec_d ori, t_vec_d dir, t_sphere *plane)
{
	t_vec_d		t;
	t_vec_d		normalize;
	t_vec_d		oc;
	double		m1;

	m1 = -1;
	normalize = (1.0 / length(plane->rotation)) * plane->rotation;
	if (dot(dir, normalize) < EPSILON)
	{
		normalize = (t_vec_d){normalize.x * m1, normalize.y * m1, normalize.z * m1};
		if (dot(dir, normalize) < EPSILON)
		{
			t.x = INFINIT;
			t.y = INFINIT;
			return (t);
		}
	}
	oc = ori - plane->center;
	t.x = dot(-oc, -normalize) / dot(dir, -normalize);
	t.y = t.x;
	return (t);
}
