/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 18:04:45 by dshereme          #+#    #+#             */
/*   Updated: 2018/11/16 01:45:12 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	int		s1_len;
	int		s2_len;
	int		idx;

	if (!s1 || !s2 || !*s1 || !*s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	idx = -1;
	if (!(newstr = (char *)malloc(s1_len + s2_len + 1)))
		return (NULL);
	newstr[s1_len + s2_len] = '\0';
	while (*s1)
	{
		newstr[++idx] = *s1;
		s1++;
	}
	while (*s2)
	{
		newstr[++idx] = *s2;
		s2++;
	}
	return (newstr);
}
