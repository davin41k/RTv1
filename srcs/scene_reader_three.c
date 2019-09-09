/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_reader_three.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 13:20:02 by dshereme          #+#    #+#             */
/*   Updated: 2019/09/09 13:20:03 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec_d		get_cam_pos(char *obj)
{
	static	t_vec_d		vec;

	vec = get_next_vec(&obj);
	return (vec);
}

t_vec_d		get_vector(int x, int y, int z)
{
	t_vec_d		vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vec_d		get_next_vec(char **fig)
{
	t_vec_d		num;

	num.x = ft_atof(*fig);
	while (**fig != ',' && **fig)
		++(*fig);
	++(*fig);
	num.y = ft_atof(*fig);
	while (**fig != ',' && **fig)
		++(*fig);
	++(*fig);
	num.z = ft_atof(*fig);
	while (**fig != ';' && **fig)
		++(*fig);
	++(*fig);
	return (num);
}

double		get_next_num(char **fig)
{
	double	num;

	num = ft_atof(*fig);
	while (**fig != ';' && **fig)
		++(*fig);
	++(*fig);
	return (num);
}

int			shift_obj_type(char **fig)
{
	while (**fig != ';' && **fig)
		++(*fig);
	++(*fig);
	return (1);
}
