/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure_factory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 19:57:20 by dshereme          #+#    #+#             */
/*   Updated: 2019/08/22 19:57:21 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_light		*get_light(int type, double intensity, t_vec_d pos, t_vec_d dir)
{
	t_light		*light;

	light = (t_light*)malloc(sizeof(t_light));
	light->type = type;
	light->intensity = intensity;
	light->pos = pos;
	light->dir = dir;
	light->next = NULL;
	return (light);
}

t_light		*get_lights(void)
{
	t_light		*light1;
	t_light		*light3;
	t_light		*light2;

	light1 = get_light(AMBIENT, 0.4, (t_vec_d){0, 0, 3}, (t_vec_d){0, 0, 3});
	light2 = get_light(POINT, 0.6, (t_vec_d){-2, 3, 0}, (t_vec_d){0, 0, 3});
	light3 = get_light(DIRECTIONAL, 0.2, (t_vec_d){0, 2, 3}, (t_vec_d){1, 4, 4});

	light1->next = light2;
	light2->next = light3;
	return (light1);
}

t_sphere		*create_sphere(t_vec_d center, double radius, t_vec_d color, int spec)
{
	t_sphere	*sphere;

	sphere = (t_sphere*)malloc(sizeof(t_sphere));
	sphere->obj_type = SPHERE;
	sphere->center = center;
	sphere->radius = radius;
	sphere->color = color;
	sphere->specular = spec;
	sphere->next = NULL;
	return (sphere);
}

t_sphere		*get_spheres(void)
{
	t_sphere	*s1;
	t_sphere	*s2;
	t_sphere	*s3;
	t_sphere	*s4;
	t_sphere	*p1;

	s1 = create_sphere((t_vec_d){-1, 2, 7}, 0.5, (t_vec_d){150, 150, 1}, 500); //желтая
	s2 = create_sphere((t_vec_d){3, 0, 4}, 1, (t_vec_d){30, 150, 30}, 10); //зеленая
	//s3 = create_sphere((t_vec_d){0, 0, 7}, 1, (t_vec_d){200, 200, 200}, 500); // белая
	s4 = create_sphere((t_vec_d){0, -5001, 7}, 5000, (t_vec_d){255, 255, 0}, 1);
	p1 = create_sphere((t_vec_d){1, 0, 10}, 1, (t_vec_d){10, 200, 200}, 1000);

	p1->obj_type = CONE;
	p1->rotation = (t_vec_d){1, 2, 0};
	p1->fig_angle = 60;
	
	p1->rotation = (t_vec_d){2, 1, 0};
	//p1->rotation =  1.0 / lngth(p1->rotation) * p1->rotation;
	p1->specular = 100;
	s1->next = s2;
	s2->next = s4;
	// s3->next = s4;
	s4->next = p1;
	return (s1);
}
