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

double	ComputeLighting(t_light *light, t_vec_d P, t_vec_d N, t_vec_d D)
{
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
		}
		light = light->next;
	}
	return (i);
}

t_vec_d	multiplay(double k, t_vec_d vec)
{
	t_vec_d re;

	re.x = vec.x * k;
	re.y = vec.y * k;
	re.z = vec.z * k;
	return (re);
}


