/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersec_ray_cylin_and_cone.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 17:43:07 by dshereme          #+#    #+#             */
/*   Updated: 2019/09/08 17:43:11 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vec_d		calc_coef_cone(t_vec_d ori, t_sphere *cone, t_vec_d dir)
{
	t_vec_d		t;
	t_vec_d		tmp;
	t_vec_d		coef;
	t_vec_d		x;
	t_vec_d		c;

	c = cone->center;
	x = ori - c;
	tmp = 1.0 / length(cone->rotation) * cone->rotation;
	coef.x = dot(dir, dir) - (1 + pow(cone->fig_angle, 2)) *
	pow(dot(dir, tmp), 2);
	coef.y = dot(dir, x) - (1 + pow(cone->fig_angle, 2)) *
	dot(x, tmp) * dot(dir, tmp);
	coef.y *= 2;
	coef.z = dot(x, x) - (1 + pow(cone->fig_angle, 2)) *
	pow(dot(x, tmp), 2.0);
	return (coef);
}

t_vec_d		intersec_ray_cone(t_vec_d ori, t_vec_d dir, t_sphere *cone)
{
	t_vec_d		k;
	t_vec_d		t_vec;
	double		discriminant;

	k = calc_coef_cone(ori, cone, dir);
	discriminant = k.y * k.y - 4 * k.x * k.z;
	if (discriminant < 0.0)
	{
		t_vec.x = INFINIT;
		t_vec.y = INFINIT;
		t_vec.z = INFINIT;
		return (t_vec);
	}
	t_vec.x = (-k.y + sqrt(discriminant)) / (2 * k.x);
	t_vec.y = (-k.y - sqrt(discriminant)) / (2 * k.x);
	t_vec.z = 0.0;
	return (t_vec);
}

t_vec_d		calc_coef_cylinder(t_vec_d ori, t_sphere *cone, t_vec_d dir)
{
	t_vec_d		t;
	t_vec_d		tmp;
	t_vec_d		coef;
	t_vec_d		x;
	t_vec_d		c;

	c = cone->center;
	x = ori - c;
	tmp = cone->rotation;
	tmp = 1.0 / length(cone->rotation) * cone->rotation;
	coef.x = dot(dir, dir) - pow(dot(dir, tmp), 2);
	coef.y = dot(dir, x) - dot(dir, tmp) * dot(x, tmp);
	coef.y *= 2;
	coef.z = dot(x, x) - pow(dot(x, tmp), 2) - cone->radius * cone->radius;
	return (coef);
}

t_vec_d		intersec_ray_cylinder(t_vec_d or, t_vec_d dir, t_sphere *cone)
{
	t_vec_d		t;
	t_vec_d		coef;
	double		discriminant;

	coef = calc_coef_cylinder(or, cone, dir);
	discriminant = coef.y * coef.y - 4 * coef.x * coef.z;
	if (discriminant < 0)
	{
		t.x = INFINIT;
		t.y = INFINIT;
		return (t);
	}
	t.x = (-coef.y + sqrt(discriminant)) / (2 * coef.x);
	t.y = (-coef.y - sqrt(discriminant)) / (2 * coef.x);
	return (t);
}
