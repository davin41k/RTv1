/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_func_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 14:00:59 by dshereme          #+#    #+#             */
/*   Updated: 2019/08/20 14:01:01 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		set_pixel(t_graph *graph, int x, int y, int color)
{
	int		tmp_x;
	int		tmp_y;

	tmp_x = WIN_HD_WIDTH / 2 + x;
	tmp_y = WIN_HD_HEIGHT / 2 - y - 1;
	if (tmp_x < 0 || tmp_x > WIN_HD_WIDTH || tmp_y < 0 ||
	tmp_y > WIN_HD_HEIGHT)
		return ;
	graph->pixs[tmp_x + tmp_y * WIN_HD_WIDTH] = color;
}

t_vec_d		get_screen_coord(int x, int y)
{
	t_vec_d		d;

	d.x = ((double)x * 1.0 / (double)WIN_FHD_WIDTH);
	d.y = ((double)y * 1.0 / (double)WIN_HD_HEIGHT);
	d.z = 1;
	return (d);
}



void	main_cycle(t_rtv *rtv)
{
	int			y;
	int			x;
	t_vec_d		dir;
	int			color;
	t_vec_d		ori;

	x = -rtv->scr_w / 2 - 1;
	ori = (t_vec_d){0, 0, 0};
	while (x++ < rtv->scr_w / 2 - 1)
	{
		y = -rtv->scr_h / 2 - 1;
		while (y++ < rtv->scr_h / 2 - 1)
		{
			dir = get_screen_coord(x, y);
			rtv->calc.dir = dir;
			camera_rotate(rtv);
			rtv->calc.dir /= 1.0 / length(rtv->calc.dir); 
			color = do_ray_trace(to_calc(rtv->calc.or, rtv->calc.dir, 1, INFINIT), rtv);
			set_pixel(rtv->graph, x, y, color);
		}
	}
}

int			interactive_elem(t_rtv *rtv)
{
	t_graph		*g;

	g = rtv->graph;
	SDL_PollEvent(&g->event);
	if ((SDL_QUIT == g->event.type) || (SDL_KEYDOWN == g->event.type &&
	SDL_SCANCODE_ESCAPE == g->event.key.keysym.scancode))
		return (-1);
	else if (g->event.type == SDL_KEYDOWN)
	{
		if (g->event.key.keysym.sym == SDLK_UP ||
		g->event.key.keysym.sym == SDLK_DOWN)
		{
			change_angle(rtv);
			main_cycle(rtv);
		}
	}
	return (0);
}

// int		new_cam_pos(t_vec_d cam_rot, t_vec_d)
// {
// 	t_vec_d		new_pos;
// 	int			i;
// 	int			j;

// 	new_pos = (t_vec_d){0, 0, 0};
// 	i = -1;
// 	j = -1;
// 	while (++i < 3)
// 	{
// 		while (++j < 3)
// 		new_cam_pos[i]
// 	}
// }

t_vec_d		new_cam_pos(int x, int y, int z)
{
	t_vec_d		new_pos;
	int			prev_x;
	int			prev_y;

	new_pos.x = (x - y) * cos(0.523599);
	new_pos.y = -z + (x + y) * sin(0.523599);
	new_pos.z = z;
	return (new_pos);
}


