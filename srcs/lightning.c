/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 15:40:58 by dshereme          #+#    #+#             */
/*   Updated: 2019/08/22 15:41:00 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

double length(t_vec_d vec)
{
 	return(sqrt(dot(vec, vec)));
}

void	do_specularity(t_shorter *sh, int spec, t_rtv *rtv, t_light *light)
{
	if (spec != -1) //зеркальность
	{
		sh->vec_r = 2.0 * dot(rtv->calc.norml, sh->l_ray) * rtv->calc.norml - sh->l_ray;
		sh->r_dot_v = dot(sh->vec_r, rtv->calc.dir);
		if (sh->r_dot_v > 0)
			sh->i +=light->intensity * pow(sh->r_dot_v / (length(sh->vec_r) * length(rtv->calc.dir)), spec);
	}
}

double		do_calc_lightning(t_rtv *rtv, t_vec_d p, int spec, t_light **l)
{
	t_light *light= *l;
	t_shorter	sh;

	sh.i = 0.0;

	if (light->type == POINT)
				sh.l_ray = light->pos - p;
			else
				sh.l_ray = light->dir;
			sh.calc = rtv->calc;
			clos_intersection(to_calc(p, sh.l_ray, EPSILON, INFINIT), &sh.calc, rtv);
			if (sh.calc.clost_spher != NULL)
			{
				light = light->next;
				return (sh.i);
			}
			sh.n_dot_l = dot(rtv->calc.norml, sh.l_ray);
			if (sh.n_dot_l > 0)
				sh.i += light->intensity * sh.n_dot_l / (length(rtv->calc.norml) * length(sh.l_ray));
			do_specularity(&sh, spec, rtv, light);
	return (sh.i);
}


double	calc_lightning(t_rtv *rtv, t_vec_d p, int spec)
{
	t_light *light= rtv->lights;
	double 	i = 0.0;
	t_vec_d	l_ray;
	double n_dot_l;
	
	double	len_normal = length(rtv->calc.norml);
	while (light)
	{
		if (light->type == AMBIENT)
			i+= light->intensity;
		else
			i += do_calc_lightning(rtv, p, spec, &light);
		light = light->next;
	}
	return (i);
}


void	check_correct_chanels(t_vec_d *color)
{
	if (color->x < 0 || color->y < 0 || color->z < 0)
		error_exit(COLOR_ERR);
	if (color->x > 255)
		color->x = 255;
	if (color->y > 255)
		color->y = 255;
	if (color->z > 255)
		color->z = 255;
}

t_vec_d	multiplay(double k, t_vec_d vec)
{
	t_vec_d re;

	re.x = vec.x * k;
	re.y = vec.y * k;
	re.z = vec.z * k;
	return (re);
}


