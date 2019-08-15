/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 15:25:36 by dshereme          #+#    #+#             */
/*   Updated: 2018/11/02 04:41:40 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*newstr;
	int		idx;
	int		len;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	if (!(newstr = (char *)malloc(len + 1)))
		return (NULL);
	newstr[len] = '\0';
	idx = -1;
	while (++idx < len)
		newstr[idx] = f(s[idx]);
	return (newstr);
}
