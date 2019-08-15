/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 17:00:01 by dshereme          #+#    #+#             */
/*   Updated: 2018/11/02 04:35:09 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	idx;

	idx = 0;
	while (idx < len)
	{
		if (*src == '\0')
		{
			dst[idx] = *src;
			idx++;
		}
		else
		{
			dst[idx] = *src;
			src++;
			idx++;
		}
	}
	return (dst);
}
