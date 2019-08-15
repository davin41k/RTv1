/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_case.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 03:43:30 by dshereme          #+#    #+#             */
/*   Updated: 2018/11/07 07:18:00 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_iscase(char chr)
{
	int		result;
	int		nbr;

	result = 0;
	nbr = ft_isalpha((int)chr);
	if (nbr)
		result = (chr < 91) ? 1 : -1;
	return (result);
}
