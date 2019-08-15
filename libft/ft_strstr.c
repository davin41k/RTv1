/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 20:20:06 by dshereme          #+#    #+#             */
/*   Updated: 2018/11/08 14:03:26 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		len;

	i = -1;
	len = ft_strlen(needle);
	if (*needle == '\0')
		return ((char *)haystack);
	while (*(haystack + ++i))
		if (ft_strncmp(haystack + i, needle, len) == 0)
			return ((char *)haystack + i);
	return (NULL);
}
