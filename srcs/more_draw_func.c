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

int			ClosestIntersection(t_vec_d O, t_vec_d D, double t_min, double t_max, t_calc *calc, t_rtv *rtv)
{
	t_light		*light = rtv->lights;
	t_sphere	*head = rtv->spheres;
	int			flag;

	flag = 0;
	calc->clost_t = 999999999;
	calc->clost_spher = NULL;

	while (head)
	{
		//t_vec_d t  = IntersectRaySphere(O, D, head);
		t_vec_d t = intersec_object(O, D, head);
		
		if (t.x >= t_min && t.x <= t_max && t.x < calc->clost_t)
		{
			calc->clost_t = t.x;
			calc->clost_spher = head;
			flag = 1;
		}
		if (t.y >= t_min && t.y <= t_max && t.y < calc->clost_t)
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

		normal = (dot(rtv->calc.D, rtv->calc.clost_spher->rotation) < 0.0 ?
		-rtv->calc.clost_spher->rotation : rtv->calc.clost_spher->rotation);
	else if (fig_type == CYLINDER)
	{
		normal = 1.0 / length(rtv->calc.clost_spher->rotation) * rtv->calc.clost_spher->rotation;
		double tmp = dot(rtv->calc.D, normal) * rtv->calc.clost_t + dot((rtv->calc.O - rtv->calc.clost_spher->center), normal);
		normal = rtv->calc.point - rtv->calc.clost_spher->center - multiplay(tmp, normal);
		//normal = dot()
		// normal = (dot(rtv->calc.D, rtv->calc.clost_spher->rotation) < 0.0 ?
		// -rtv->calc.clost_spher->rotation : rtv->calc.clost_spher->rotation);

		// tmp = dot(rtv->calc.D, rtv->calc.clost_spher->rotation) * rtv->calc.L
		// + dot((rtv->calc.O - rtv->calc.clost_spher->center), rtv->calc.clost_spher->rotation);
		// normal = rtv->calc.clost_spher->rotation / sqrt(dot(rtv->calc.clost_spher->rotation, rtv->calc.clost_spher->rotation));
	}
	else if (fig_type == CONE)
	{
		
	}
	return (normal);
}

t_vec_d		intersec_object(t_vec_d O, t_vec_d D, t_sphere *obj)
{
	t_vec_d		t;

	if (obj->obj_type == SPHERE)
		t = IntersectRaySphere(O, D, obj);
	else if (obj->obj_type == PLANE)
		t = intersec_ray_plane(O, D, obj);
	else if (obj->obj_type == CYLINDER)
		t = intersec_ray_cylinder(O, D, obj);
	else if (obj->obj_type == CONE)
		t = intersec_ray_cone(O, D, obj);
	return (t);
}

t_vec_d		intersec_ray_cone(t_vec_d O, t_vec_d D, t_sphere *cone)
{
	t_vec_d		t;
	t_vec_d		k;
	t_vec_d		tmp;

	t_vec_d C = cone->center;
	double r = cone->radius;
	t_vec_d x = O - C;

	tmp = cone->rotation; 
	tmp = 1.0 / length(cone->rotation) * cone->rotation;
	k.x = dot(D, D) - (1 + pow(cone->fig_angle, 2)) * pow(dot(D, tmp), 2);
	k.y = dot(D, x) - (1 + pow(cone->fig_angle, 2)) * dot(x, tmp) * dot(D, tmp);
	k.y *= 2;
	k.z = dot(x, x) - (1 + pow(cone->fig_angle, 2)) * pow(dot(x, tmp), 2.0);
	
	double discriminant = k.y * k.y - 4 * k.x * k.z;	
	if (discriminant < 0.0)
		{
			t.x = 99999999999;
			t.y = 99999999999;
			t.z = 99999999999;
			return (t);
		}
	t.x = (-k.y + sqrt(discriminant)) / (2 * k.x);
	t.y = (-k.y - sqrt(discriminant)) / (2 * k.x);
	t.z = 0.0;
	return (t);
}

t_vec_d		intersec_ray_plane(t_vec_d O, t_vec_d D, t_sphere *plane)
{
	t_vec_d		t;
	t_vec_d		normalize;



	normalize = (1.0 / length(plane->rotation)) * plane->rotation;

	if (dot(D, normalize) < 0.0001)
	{
		if (dot(D, -normalize) < 0.0001)
        {
            t.x = 999999999;
            t.y = 999999999;
            return (t);
        }
	}
	t_vec_d oc = O - plane->center;
	t.x = dot(-oc, -normalize) / dot(D, -normalize);
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

t_vec_d		intersec_ray_cylinder(t_vec_d O, t_vec_d D, t_sphere *cone)
{
	t_vec_d    t;
	t_vec_d    k;
	t_vec_d		tmp;

	t_vec_d C = cone->center;
	double r = cone->radius;
	t_vec_d x = O - C;

	tmp = cone->rotation; 
	tmp = 1.0 / length(cone->rotation) * cone->rotation;
	k.x = dot(D, D) - pow(dot(D, tmp),2);
	k.y = dot(D, x) - dot(D, tmp) * dot(x, tmp);
	k.y *= 2;
	k.z = dot(x, x) - pow(dot(x, tmp), 2) - cone->radius * cone->radius;
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

// t_vec_d		intersec_ray_cone(t_vec_d O, t_vec_d D, t_sphere *cone)
// {
	
// }



void		calc_init(t_vec_d O, t_vec_d D, t_calc *calc)
{
	calc->O = O;
	calc->D = D;
}
