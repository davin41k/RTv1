/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 13:57:27 by dshereme          #+#    #+#             */
/*   Updated: 2018/11/08 14:43:24 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isdigit(int c)
{
	return (c > 47 && c < 58);
}