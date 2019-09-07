/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 15:56:16 by dshereme          #+#    #+#             */
/*   Updated: 2019/08/30 15:56:23 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char		*check_null_str(char *s, int c)
{
	char *s1;

	if (s == NULL)
		return (NULL);
	s1 = (char *)s;
	while (*s1 == 32 || (*s1 <= 13 && *s1 >= 9) || *s1 == '-' || *s1 == '0')
		s1++;
	while (*s1)
	{
		if ((*s1 < 48 || *s1 > 57) && *s1 != 46)
			return (NULL);
		if (*s1 == (unsigned char)c)
			return (s1);
		s1++;
	}
	if (*s1 == (unsigned char)c)
		return (s1);
	return (NULL);
}

static    int    find_zero(char **s)
{
	int count_zero;

	(*s)++;
	count_zero = 0;
	while (**s == '0')
	{
		(*s)++;
		count_zero++;
	}
	return (count_zero);
}

int			tester(char *nptr)
{
	char    *str;
	int        i;
	int        d;

	i = 0;
	d = 1;
	str = nptr;
	while (str[i] == 32 || (str[i] <= 13 && str[i] >= 9))
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			d = -1;
		i++;
	}
	return (d);
}

double		ft_atof(char *nptr)
{
	double    mant;
	char    *ch;
	double    atf;
	int        count_zero;
	int        castul;

	castul = 1;
	mant = (double)ft_atoi(nptr);
	if (mant == 0)
		castul = tester(nptr);
	if ((ch = check_null_str(nptr, '.')) == NULL)
		return (mant);
	count_zero = find_zero(&ch);
	atf = (double)ft_atoi(ch);
	while (atf > 1)
		atf /= 10;
	while (count_zero)
	{
		count_zero--;
		atf /= 10;
	}
	atf += mant;
	atf *= castul;
	return (atf);
}
