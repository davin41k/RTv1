/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 00:19:42 by dshereme          #+#    #+#             */
/*   Updated: 2018/11/02 04:33:44 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;
	unsigned char	symb;

	str = (unsigned char *)s;
	i = 0;
	symb = (unsigned char)c;
	while ((i != n))
	{
		if (*str == symb)
			return (str);
		i++;
		str++;
	}
	return (NULL);
}
