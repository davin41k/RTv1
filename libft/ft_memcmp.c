/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 01:12:35 by dshereme          #+#    #+#             */
/*   Updated: 2018/11/07 01:28:52 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			idx;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	idx = 0;
	while (idx < n && s1[idx] == s2[idx])
		idx++;
	return ((idx == n) ? 0 : *(s1 + idx) - *(s2 + idx));
}
