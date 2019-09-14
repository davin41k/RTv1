/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:26:37 by dshereme          #+#    #+#             */
/*   Updated: 2019/09/11 17:26:39 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

// void	load_texture(t_rtv *rtv, char *text_path)
// {
// 	static	int		texture_numb;
// 	SDL_Surface		*img;
// 	int				count_pix;
// 	int				*pixels;
// 	int				idx;

// 	count_pix = get_textures_pix_count();
// 	idx = -1;
// 	if (!(pixels = (int*)ft_memalloc(sizeof(int) * count_pix)))
// 		error_exit(MEM_ERR);
// 	img = SDL_LoadBMP(text_path);
// 	if (img == NULL)
// 		error_exit(LOAD_ERR);
// 	while (++idx < count_pix)
// 		pixels[idx] = get_texel(img->pixels, idx * 3);
// 	if (texture_numb > 7)
// 	{
// 		error_exit(LOAD_ERR);
// 		SDL_FreeSurface(img);
// 	}
// 	rtv->textures[texture_numb++] = pixels;
// 	SDL_FreeSurface(img);
// }
void	load_texture(t_rtv *rtv, char *text_path)
{
	rtv->texture = SDL_LoadBMP(text_path);
	if (rtv->texture == NULL)
		error_exit(LOAD_ERR);
		int i = -1;
		int	*arr = (int*)rtv->texture->pixels;
		// while (++i < 100)
		// 	printf("c%d:\t%d\n", i, arr[i]);
}

int		get_texel(void *pixels, int idx)
{
	unsigned	char	*pix;
	unsigned	int		red;
	unsigned	int		green;
	unsigned	int		blue;

	pix = (unsigned char*)pixels;
	blue = pix[idx];
	green = pix[idx + 1] << 8;
	red = pix[idx + 2] << 16;
	return (red | green | blue);
}

t_vec_d color_to_vec(int rgb)
{
	unsigned	int			red;
	unsigned	int			green;
	unsigned	int			blue;
    
	red = (rgb >> 16) & 0xFF;
    green = (rgb >> 8) & 0xFF ;
    blue = (rgb) & 0xFF;
	return ((t_vec_d){red, green, blue});
}

// Uint32	rt_uv_sphere(SDL_Surface *restrict const tex, t_v4df const n)
// {
// 	__v2si	uv;

// 	uv = (__v2si){ (0.5 + atan2(Z(n), X(n)) / (2.0 * M_PI)) * tex->w,
// 					tex->h - ((0.5 - asin(Y(n)) / M_PI) * tex->h) };
// 	return (((Uint32*)tex->pixels)[Y(uv) * tex->w + X(uv)]);
// }

t_vec_d		texture_mapping(t_rtv *rtv, t_vec_d p)
{
	int		u, v;
	t_vec_d		color;
	Uint32		clr;
	p -= rtv->calc.clost_spher->center;
	p = normalize(p);
	u = (0.5 + atan2(p.z, p.x) / (2.0 * M_PI)) * rtv->texture->w; //0 .. 1
	v = rtv->texture->h - ((0.5 - asin(p.y) / M_PI) * rtv->texture->h); // 0 .. 1
	// u *= (rtv->texture->w );
	// v *= (rtv->texture->h);
	//printf("u:\t%f\tv:\t%f\n", u, v);
	// color = ((Uint32*)rtv->texture->pixels)[(int)(v * rtv->texture->w + u)]; //1024 * 680
	
	// clr = ((Uint32*)rtv->texture->pixels)[(u * rtv->texture->w + v)]; //1024 * 680
	clr = (Uint32*)get_texel(rtv->texture->pixels, (u * rtv->texture->w + v) * 3); //1024 * 680
	color = color_to_vec(clr);
	//printf("color:\t%d\t color:  %f   %f   %f\n", clr, color.x, color.y, color.z);
	return ((t_vec_d)color);
}

double		ft_max(double a, double b)
{
	return (a > b ? a : b);
}



t_vec_d		procedural_texturing(t_vec_d point, t_light *lights, t_calc calc)
{
	t_vec_d		color = calc.color;
	double		scale_s = 5;
	double		pattern = (sin(point.x * 2 * M_PI * scale_s) + 1 * 0.5);
	color = calc.clost_spher->color;
	while (lights->next)
	{
		color.x += 100 * pattern * ft_max(0.f, dot(-lights->dir, (t_vec_d){1, 1, 1}));
		color.y += 100 * pattern * ft_max(0.f, dot(-lights->dir, (t_vec_d){1, 1, 1}));
		color.z += 100 * pattern * ft_max(0.f, dot(-lights->dir, (t_vec_d){1, 1, 1}));
		printf("%f\n", color.x);

		lights = lights->next;
	}
	// printf("old:\t%f\tnew:\t%f\n", calc.clost_spher->color.x, color.x);	
	return (color);
}
