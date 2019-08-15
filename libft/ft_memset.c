/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <dshereme@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 23:01:03 by dshereme          #+#    #+#             */
/*   Updated: 2018/11/05 18:03:21 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *destination, int c, size_t len)
{
	size_t			i;
	unsigned char	symbol;
	unsigned char	*d;

	symbol = (unsigned char)c;
	d = (unsigned char *)destination;
	i = 0;
	while (i < len)
	{
		d[i] = symbol;
		i++;
	}
	return (destination);
}
