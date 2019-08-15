/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countdigit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 05:01:50 by dshereme          #+#    #+#             */
/*   Updated: 2018/11/07 07:19:10 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_countdigit(int n)
{
	int		tens;
	int		newchar;

	if (n == -2147483648)
		return (10);
	if (n == 2147483647)
		return (10);
	tens = 1;
	newchar = 10;
	if (n < 0)
		n *= -1;
	while (1)
	{
		if (n < newchar)
			break ;
		newchar *= 10;
		tens++;
	}
	return (tens);
}
