/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 15:47:43 by dshereme          #+#    #+#             */
/*   Updated: 2018/11/02 04:41:54 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	idx;
	unsigned int	len;
	char			*newstr;

	if (!s || !f)
		return (NULL);
	idx = 0;
	len = ft_strlen(s);
	if (!(newstr = (char *)malloc(len + 1)))
		return (NULL);
	newstr[len] = '\0';
	while (idx < len)
	{
		newstr[idx] = f(idx, s[idx]);
		idx++;
	}
	return (newstr);
}
