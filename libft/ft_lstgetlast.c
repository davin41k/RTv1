/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstgetlast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 23:42:29 by dshereme          #+#    #+#             */
/*   Updated: 2018/11/07 06:44:13 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstgetlast(t_list **list)
{
	t_list	*head;

	head = NULL;
	if (!list || !*list)
		return (head);
	head = *list;
	while (head->next)
		head = head->next;
	return (head);
}
