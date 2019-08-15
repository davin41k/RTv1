/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 22:16:48 by dshereme          #+#    #+#             */
/*   Updated: 2018/11/08 17:22:08 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*list;

	if (!alst || !*alst || !del)
		return ;
	list = *alst;
	while (*alst)
	{
		del((*alst)->content, (*alst)->content_size);
		free(list);
		*alst = (*alst)->next;
		list = *alst;
	}
}
