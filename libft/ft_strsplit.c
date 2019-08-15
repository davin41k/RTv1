/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 01:17:55 by dshereme          #+#    #+#             */
/*   Updated: 2018/11/10 19:20:21 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*unostr(const char *str, char chr, int *idx)
{
	int		start;
	int		end;

	while (str[*idx] == chr)
		*idx += 1;
	start = *idx;
	while (str[*idx] != chr && str[*idx])
		*idx += 1;
	end = *idx - 1;
	if (end == -1 || str[start] == '\0')
		return (NULL);
	return (ft_strsub(str, (unsigned int)start, (size_t)(end - start + 1)));
}

static	int		count_str(const char *str, char chr)
{
	int		idx;
	int		count;

	idx = 0;
	count = 0;
	while (str[idx])
	{
		while (str && str[idx] == chr)
			idx++;
		if (str[idx] != chr && str[idx])
			count++;
		while (str[idx] != chr && str[idx])
			idx++;
	}
	return (count);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**restr;
	int		idx;
	int		strings;

	if (!s)
		return (NULL);
	idx = 0;
	strings = 0;
	if (!(restr = (char **)malloc(sizeof(char *) * (count_str(s, c) + 1))))
		return (NULL);
	while (s[idx])
		restr[strings++] = unostr(s, c, &idx);
	if (restr[strings - 1] != NULL)
		restr[strings] = NULL;
	return (restr);
}
