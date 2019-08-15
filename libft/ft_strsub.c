/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 16:55:44 by dshereme          #+#    #+#             */
/*   Updated: 2018/11/06 17:39:48 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*newstr;
	size_t	idx;

	if (!s)
		return (NULL);
	if (!(newstr = (char *)malloc(len + 1)))
		return (NULL);
	idx = 0;
	while (idx < len)
	{
		newstr[idx] = s[start + idx];
		idx++;
	}
	newstr[len] = '\0';
	return (newstr);
}
