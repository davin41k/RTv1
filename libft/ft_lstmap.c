/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 19:17:57 by dshereme          #+#    #+#             */
/*   Updated: 2018/11/11 19:09:38 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*head;
	t_list	*newlist;

	if (!lst || !f)
		return (NULL);
	newlist = f(lst);
	head = newlist;
	while (lst->next)
	{
		if (!(head->next = f(lst->next)))
		{
			free(head->next);
			return (NULL);
		}
		head = head->next;
		lst = lst->next;
	}
	return (newlist);
}
