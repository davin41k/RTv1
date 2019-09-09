/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 19:57:20 by dshereme          #+#    #+#             */
/*   Updated: 2019/08/31 19:57:22 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"


void	print_vec(char *vec_name, t_vec_d vec)
{
	printf("%s:\t->\t%f\t%f\t%f\n", vec_name, vec.x, vec.y, vec.z);
}

void	print_state(char *state, double value)
{
	printf("%s:\t->\t%f\n", state, value);
}

void	print_object(t_sphere *sphere)
{
	print_state("obj_type", sphere->obj_type);
	print_vec("center", sphere->center);
	print_state("radius", sphere->radius);
	print_vec("color", sphere->color);
	print_vec("rotation", sphere->rotation);
	print_state("specular", sphere->specular);
	print_state("fig_angle", sphere->fig_angle);
}

void	print_light(t_light *light)
{
	print_state("light_type", light->type);
	print_state("intensity", light->intensity);
	print_vec("pos", light->pos);
	print_vec("dir", light->dir);
}

void	print_all_objects(t_rtv *rtv)
{
	t_sphere	*sphere;
	t_light		*light;

	sphere = rtv->spheres;
	light = rtv->lights;

	while(sphere)
	{
		printf("OOOOOOOOOOO\n");
		print_object(sphere);
		sphere = sphere->next;
	}
	while(light)
	{
		printf("LLLLLLLLLLLL\n");
		print_light(light);
		light = light->next;
	}
}
