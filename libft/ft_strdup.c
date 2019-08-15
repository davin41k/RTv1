/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 00:56:10 by dshereme          #+#    #+#             */
/*   Updated: 2018/11/13 12:26:59 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*newstr;
	int		idx;
	int		len;

	idx = -1;
	len = ft_strlen(s1);
	if (!(newstr = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (++idx < len)
		newstr[idx] = s1[idx];
	newstr[idx] = '\0';
	return (newstr);
}
