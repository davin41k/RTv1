/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_reader_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 13:18:28 by dshereme          #+#    #+#             */
/*   Updated: 2019/09/09 13:18:30 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		nullify_object(t_sphere *obj)
{
	obj->center = (t_vec_d) {0, 0, 0};
	obj->radius = 1;
	obj->color = (t_vec_d) {200, 200, 200};
	obj->rotation = (t_vec_d) {0, 0, 0};
	obj->specular = 0;
	obj->fig_angle = 0;
	obj->next = NULL;
}

void		nullify_light(t_light *light)
{
	light->intensity = 0;
	light->pos = (t_vec_d) {0, 0, 0};
	light->dir = (t_vec_d) {0, 0, 0};
	light->next = NULL;
}

t_sphere	*get_sphere(char *obj)
{
	t_sphere	*sphere;
	char		*save_str;

	if (!(sphere = (t_sphere*)ft_memalloc(sizeof(t_sphere))))
		error_exit(MEM_ERR);
	save_str = obj;
	nullify_object(sphere);
	sphere->obj_type = get_obj_type(obj);
	shift_obj_type(&obj);
	sphere->center = get_next_vec(&obj);
	sphere->radius = get_next_num(&obj);
	sphere->color = get_next_vec(&obj);
	sphere->rotation = get_next_vec(&obj);
	sphere->specular = (int)get_next_num(&obj);
	sphere->fig_angle = get_next_num(&obj);
	return (sphere);
}

t_light		*create_light(char *obj)
{
	t_light		*light;

	if (!(light = (t_light*)ft_memalloc(sizeof(t_light))))
		error_exit(MEM_ERR);
	nullify_light(light);
	light->type = get_obj_type(obj);
	shift_obj_type(&obj);
	light->intensity = get_next_num(&obj);
	light->pos = get_next_vec(&obj);
	light->dir = get_next_vec(&obj);
	return (light);
}
