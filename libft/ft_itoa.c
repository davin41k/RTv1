/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 01:56:46 by dshereme          #+#    #+#             */
/*   Updated: 2018/11/10 18:50:46 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	counter(int n)
{
	int		i;

	i = 1;
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	char	*restr;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = counter(n);
	if (!(restr = (char *)malloc(len + 1)))
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		restr[0] = '-';
	}
	restr[len--] = '\0';
	while (len)
	{
		if (n < 10)
			break ;
		restr[len--] = n % 10 + '0';
		n /= 10;
	}
	restr[len] = n + '0';
	return (restr);
}
