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

void		calc_init(t_vec_d or, t_vec_d dir, t_calc *calc)
{
	calc->or = or;
	calc->dir = dir;
}
