/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 19:58:47 by dshereme          #+#    #+#             */
/*   Updated: 2018/11/12 17:09:58 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t length)
{
	int		i;
	char	*s_dst;
	char	*s_src;
	int		len;

	i = 0;
	len = (int)length;
	s_dst = (char *)dst;
	s_src = (char *)src;
	if ((s_src) < (s_dst))
		while (--len >= 0)
			s_dst[len] = s_src[len];
	else
	{
		while (i < len)
		{
			s_dst[i] = s_src[i];
			i++;
		}
	}
	return (dst);
}
