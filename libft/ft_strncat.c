/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 04:13:01 by dshereme          #+#    #+#             */
/*   Updated: 2018/11/02 04:35:40 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	int		len_s1;
	size_t	count;

	len_s1 = ft_strlen(s1);
	count = 0;
	while ((count < n) && (s2[count] != '\0'))
	{
		s1[len_s1] = s2[count];
		count++;
		len_s1++;
	}
	s1[len_s1] = '\0';
	return (s1);
}
