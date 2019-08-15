/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 19:18:22 by dshereme          #+#    #+#             */
/*   Updated: 2018/11/06 19:10:47 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	less_start_ws(const char *s)
{
	int		count;

	count = 0;
	while (*s == ' ' || *s == '\t' || *s == '\n')
	{
		count++;
		s++;
	}
	return (count);
}

static	int	less_end_ws(const char *s)
{
	int		i;
	int		count;

	i = ft_strlen(s) - 1;
	count = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
	{
		i--;
		count++;
	}
	return (count);
}

char		*ft_strtrim(char const *s)
{
	char	*restr;
	int		ws_start;
	int		ws_end;
	int		l;

	if (!s)
		return (NULL);
	ws_start = less_start_ws(s);
	ws_end = less_end_ws(s);
	l = ft_strlen(s);
	if (ws_start == l)
		return (ft_strnew(1));
	restr = ft_strsub(s, less_start_ws(s), l - ws_end - ws_start);
	return (restr);
}
