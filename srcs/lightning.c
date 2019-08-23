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

double	ComputeLighting(t_rtv *rtv, t_vec_d P, t_vec_d N, t_vec_d D, int spec)
{
	t_light *light= rtv->lights;
	double 	i = 0.0;
	t_vec_d	L = light->pos - D;
	double n_dot_l;
	
	double	len_normal = length(N);
	while (light)
	{
		if (light->type == AMBIENT)
			i+= light->intensity;
		else
		{
			if (light->type == POINT)
				L = light->pos - P;
			else
				L = light->dir;
			n_dot_l = dot(N, L);
			if (n_dot_l > 0)
				i += light->intensity * n_dot_l / (len_normal * length(L));
			if (spec != -1)
			{
				t_vec_d vec_r = 2.0 * dot(N, L) * N - L;
				double r_dot_v = dot(vec_r, D);
				if (r_dot_v > 0) {
					//printf("AFTER POW %f, \n", pow(r_dot_v / (length(vec_r) * length(D)), spec));
					i +=light->intensity * pow(r_dot_v / (length(vec_r) * length(D)), spec); }
				//printf("%f, i\n");
			}
		}
		light = light->next;
	}
	return (i);
}

void	check_correct_chanels(t_vec_d *color)
{
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


