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

int			ClosestIntersection(double t_min, double t_max, t_rtv *rtv)
{
	t_light		*light = rtv->lights;
	t_sphere	*head = rtv->spheres;
	int			flag;

	flag = 0;
	rtv->calc.clost_t = 999999999;
	rtv->calc.clost_spher = NULL;


	while (head)
	{
		t_vec_d t  = IntersectRaySphere(rtv->calc.O, rtv->calc.D, head);
		if (t.x >= t_min && t.x <= t_max && t.x < rtv->calc.clost_t)
		{
			rtv->calc.clost_t = t.x;
			rtv->calc.clost_spher = head;
			flag = 1;
		}
		if (t.y >= t_min && t.y <= t_max && t.y < rtv->calc.clost_t)
		{
			rtv->calc.clost_t = t.y;
			rtv->calc.clost_spher = head;
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
