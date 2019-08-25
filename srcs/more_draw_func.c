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
		t_vec_d t  = IntersectRaySphere(O, D, head);
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


void		calc_init(t_vec_d O, t_vec_d D, t_calc *calc)
{
	calc->O = O;
	calc->D = D;
}
