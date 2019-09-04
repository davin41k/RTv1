/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_draw_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 17:28:32 by dshereme          #+#    #+#             */
/*   Updated: 2019/08/23 17:28:33 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_calc		to_calc(t_vec_d or, t_vec_d dir, double t_min, double t_max)
{
	t_calc		calc;

	calc.or = or;
	calc.dir = dir;
	calc.t_min = t_min;
	calc.t_max = t_max;
	return (calc);
}

int			clos_intersection(t_calc c, t_calc *calc, t_rtv *rtv)
{
	t_light		*light = rtv->lights;
	t_sphere	*head = rtv->spheres;
	int			flag;

	flag = 0;
	calc->clost_t = INFINIT;
	calc->clost_spher = NULL;

	while (head)
	{
		//t_vec_d t  = IntersectRaySphere(O, D, head);
		t_vec_d t = intersec_object(c.or, c.dir, head);
		
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
		head = head->next;
	}
	return (flag);
}

t_vec_d		calc_normal(t_rtv *rtv, int fig_type)
{
	t_vec_d		normal;
	t_vec_d		tmp;

	if (fig_type == SPHERE)
	{
		normal = rtv->calc.point - rtv->calc.clost_spher->center;
		normal = multiplay( 1.0 / length(normal), normal);
	}
	else if (fig_type == PLANE)
		// normal = (1.0 / length(rtv->calc.clost_spher->rotation)) * rtv->calc.clost_spher->rotation; 

		normal = (dot(rtv->calc.dir, rtv->calc.clost_spher->rotation) < 0.0 ?
		-rtv->calc.clost_spher->rotation : rtv->calc.clost_spher->rotation);
	else if (fig_type == CYLINDER || fig_type == CONE)
	{
		normal = 1.0 / length(rtv->calc.clost_spher->rotation) * rtv->calc.clost_spher->rotation;
		double tmp = dot(rtv->calc.dir, normal) * rtv->calc.clost_t + dot((rtv->calc.or - rtv->calc.clost_spher->center), normal);
		normal = rtv->calc.point - rtv->calc.clost_spher->center - multiplay(tmp, normal);
		//normal = dot()
		// normal = (dot(rtv->calc.D, rtv->calc.clost_spher->rotation) < 0.0 ?
		// -rtv->calc.clost_spher->rotation : rtv->calc.clost_spher->rotation);

		// tmp = dot(rtv->calc.D, rtv->calc.clost_spher->rotation) * rtv->calc.L
		// + dot((rtv->calc.O - rtv->calc.clost_spher->center), rtv->calc.clost_spher->rotation);
		// normal = rtv->calc.clost_spher->rotation / sqrt(dot(rtv->calc.clost_spher->rotation, rtv->calc.clost_spher->rotation));
	}
	else
	{
		double m = dot(rtv->calc.dir, normal) * rtv->calc.clost_t + dot((rtv->calc.or - rtv->calc.clost_spher->center), normal);
		double a = rtv->calc.clost_spher->radius * rtv->calc.clost_spher->radius / m;
		normal = (rtv->calc.point -  rtv->calc.clost_spher->rotation -  rtv->calc.dir * m - rtv->calc.dir * a);
		normal = 1.0 / length(normal);
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

t_vec_d		intersec_ray_cone(t_vec_d or, t_vec_d dir, t_sphere *cone)
{
	t_vec_d		t;
	t_vec_d		k;
	t_vec_d		tmp;

	t_vec_d C = cone->center;
	double r = cone->radius;
	t_vec_d x = or - C;

	tmp = cone->rotation; 
	tmp = 1.0 / length(cone->rotation) * cone->rotation;
	k.x = dot(dir, dir) - (1 + pow(cone->fig_angle, 2)) * pow(dot(dir, tmp), 2);
	k.y = dot(dir, x) - (1 + pow(cone->fig_angle, 2)) * dot(x, tmp) * dot(dir, tmp);
	k.y *= 2;
	k.z = dot(x, x) - (1 + pow(cone->fig_angle, 2)) * pow(dot(x, tmp), 2.0);
	
	double discriminant = k.y * k.y - 4 * k.x * k.z;	
	if (discriminant < 0.0)
		{
			t.x = INFINIT;
			t.y = INFINIT;
			t.z = INFINIT;
			return (t);
		}
	t.x = (-k.y + sqrt(discriminant)) / (2 * k.x);
	t.y = (-k.y - sqrt(discriminant)) / (2 * k.x);
	t.z = 0.0;
	return (t);
}

t_vec_d		intersec_ray_plane(t_vec_d or, t_vec_d dir, t_sphere *plane)
{
	t_vec_d		t;
	t_vec_d		normalize;



	normalize = (1.0 / length(plane->rotation)) * plane->rotation;

	if (dot(dir, normalize) < EPSILON)
	{
		if (dot(dir, -normalize) < EPSILON)
        {
            t.x = INFINIT;
            t.y = INFINIT;
            return (t);
        }
	}
	t_vec_d oc = or - plane->center;
	t.x = dot(-oc, -normalize) / dot(dir, -normalize);
	t.y = t.x;

	// t.x = ((dot(plane->rotation, plane->center)) - dot(O, plane->center));
	// t.y = t.x;
	// dot(plane->rotation, D);
	// if (t.x < 0.0001) {
	// 	t.x = 999999999;
	// 	t.y = 999999999;
	// }
	return (t);
}

t_vec_d		intersec_ray_cylinder(t_vec_d or, t_vec_d dir, t_sphere *cone)
{
	t_vec_d    t;
	t_vec_d    k;
	t_vec_d		tmp;

	t_vec_d C = cone->center;
	double r = cone->radius;
	t_vec_d x = or - C;

	tmp = cone->rotation; 
	tmp = 1.0 / length(cone->rotation) * cone->rotation;
	k.x = dot(dir, dir) - pow(dot(dir, tmp),2);
	k.y = dot(dir, x) - dot(dir, tmp) * dot(x, tmp);
	k.y *= 2;
	k.z = dot(x, x) - pow(dot(x, tmp), 2) - cone->radius * cone->radius;
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

void		calc_init(t_vec_d or, t_vec_d dir, t_calc *calc)
{
	calc->or = or;
	calc->dir = dir;
}
