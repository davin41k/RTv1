/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 15:23:18 by dshereme          #+#    #+#             */
/*   Updated: 2019/08/16 15:23:44 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	clean_text(char **splitted)
{
	int		i;

	i = -1;
	while (splitted[++i])
		free(splitted[i]);
	free(splitted);
}
