/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 19:31:08 by dshereme          #+#    #+#             */
/*   Updated: 2019/08/15 19:31:10 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		escape_exit(int key)
{
	if (key == 53)
	{
		exit(0);
	}
	return (0);
}

int		red_exit(int key)
{
	(void)key;
	exit(0);
	return (0);
}

void	read_error(void)
{
	ft_putendl("a map read error");
	exit(0);
}

void	error_exit(int errno)
{
	if (errno == USAGE)
	{
		ft_putendl("usage:    ./RTv1 a_scene_file.rtv1:");
		ft_putendl("one object in one line in the file");
	}
	else if (errno == THREAD_ERR)
		ft_putendl("thread error");
	else if (errno == MEM_ERR)
		ft_putendl("memory error");
	else if (errno == SCENE_ERR)
		ft_putendl("error: scene is not correct");
	else if (errno == INCORRECT_MAP)
		ft_putendl("error: map is too big or too small");
	else if (errno == LOAD_ERR)
		ft_putendl("error: textures was not load");
	else if (errno == FORMAT_ERR)
		ft_putendl("error: map have different format");
	exit(0);
}
