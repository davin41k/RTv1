/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_reader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 13:20:13 by dshereme          #+#    #+#             */
/*   Updated: 2019/08/30 13:20:16 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			read_scene(t_rtv *rtv)
{
	int		fd;
	char	*object;

	fd = open(rtv->scenes_file, O_RDONLY);
	printf("fd:\t%d\n", fd);
	printf("file_name:\t%s\n", rtv->scenes_file);
	while (get_next_line(fd, &object))
	{
		if (*object != EMPTY_LINE)
			get_object(object, rtv);
		free(object);
	}
	close(fd);
	return (1);
}

int			check_map_format(char *file_name)
{
	char	**split;
	int		idx;
	int		fd;
	char	*tmp;

	tmp = NULL;
	idx = 0;
	split = NULL;
	fd = open(file_name, O_RDONLY);
	if (read(fd, tmp, 0) == -1)
		error_exit(FORMAT_ERR);
	close(fd);
	ft_strdel(&tmp);
	split = ft_strsplit(file_name, '.');
	while (split[idx])
		idx++;
	if (!ft_strequ(split[--idx], MAP_FORMAT))
	{
		clean_text(split);
		error_exit(FORMAT_ERR);
	}
	else
		clean_text(split);
	return (1);
}

void		get_object(char *object, t_rtv *rtv)
{
	t_sphere	*new_sphere;
	t_sphere	*old_sphere;
	t_light		*old_light;
	t_light		*new_light;

	if (get_abstract_obj_type(object) == FIGURE)
	{
		old_sphere = rtv->spheres;
		new_sphere = get_sphere(object);
		rtv->spheres = new_sphere;
		new_sphere->next = old_sphere;
		check_correct_chanels(&rtv->spheres->color);
	}
	else if (get_abstract_obj_type(object) == LIGHT)
	{
		old_light = rtv->lights;
		new_light = create_light(object);
		rtv->lights = new_light;
		new_light->next = old_light;
	}
	else if (get_abstract_obj_type(object) == CAMERA)
		rtv->calc.or = get_cam_pos(object);
}

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
	sphere->obj_type = get_obj_type(obj); //СМЕСТИТЬ!!!
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

	// num = get_vector(1, 1, 1);
	// if (!**fig)
	// 	return (num);
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

int			get_abstract_obj_type(char *obj)
{
	int		type;
	int		abstract_type;

	type = get_obj_type(obj);
	if (type == PLANE || type == SPHERE || type == CONE || type == CYLINDER)
		abstract_type = FIGURE;
	else if (type == AMBIENT || type == POINT || type == DIRECTIONAL)
		abstract_type = LIGHT;
	else if (type == CAMERA)
		abstract_type = CAMERA;
	else
		error_exit(SCENE_ERR);
	return (abstract_type);
}

int			shift_obj_type(char **fig)
{
	while (**fig != ';' && **fig)
		++(*fig);
	++(*fig);
	return (1);
}

int			get_obj_type(char *object)
{
	int		type;

	if (ft_strstr(object, "SPHERE"))
		type = SPHERE;
	else if (ft_strstr(object, "PLANE"))
		type = PLANE;
	else if (ft_strstr(object, "CONE"))
		type = CONE;
	else if (ft_strstr(object, "CYLINDER"))
		type = CYLINDER;
	else if (ft_strstr(object, "AMBIENT"))
		type = AMBIENT;
	else if (ft_strstr(object, "POINT"))
		type = POINT;
	else if (ft_strstr(object, "DIRECTIONAL"))
		type = DIRECTIONAL;
	else if (ft_strstr(object, "CAMERA"))
		type = CAMERA;
	else
		error_exit(SCENE_ERR);
	return (type);
}
