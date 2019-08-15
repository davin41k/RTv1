/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 23:31:55 by dshereme          #+#    #+#             */
/*   Updated: 2018/11/08 16:41:54 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstcount(t_list **list)
{
	int		count;
	t_list	*head;

	if (!list || !*list)
		return (0);
	count = 0;
	head = *list;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}
