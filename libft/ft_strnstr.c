/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 19:33:34 by dshereme          #+#    #+#             */
/*   Updated: 2018/11/08 14:11:39 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		length;
	int		i;
	int		ilen;

	length = ft_strlen(needle);
	i = -1;
	ilen = len;
	if (!*needle)
		return ((char *)haystack);
	while (*(haystack + ++i) && (i + length) <= ilen)
		if (!ft_strncmp(haystack + i, needle, length))
			return ((char *)haystack + i);
	return (NULL);
}
