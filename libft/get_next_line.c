/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <dshereme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 14:01:28 by dshereme          #+#    #+#             */
/*   Updated: 2019/04/13 15:47:38 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

static	t_list		*get_list(int fd, t_list **list_head)
{
	t_list	*head;

	head = *list_head;
	while (head != NULL && (int)head->content_size != fd)
		head = head->next;
	if (head == NULL)
	{
		head = ft_lstnew(NULL, fd);
		head->content_size = fd;
		head->next = *list_head;
		*list_head = head;
	}
	return (head);
}

static	int			fill_buffer(int fd, t_list *list)
{
	char	*tmp;
	void	*lstcontent;
	int		ret;

	if (list->content && ft_strchr(list->content, '\n'))
		return (1);
	tmp = malloc(sizeof(char) * (BUFF_SIZE + 1));
	while ((ret = read(fd, tmp, BUFF_SIZE)) > 0)
	{
		tmp[ret] = '\0';
		lstcontent = list->content;
		if ((!list->content && *tmp) ||
		(list->content && ((char *)list->content)[0] == '\0'))
			list->content = ft_strdup(tmp);
		else
			list->content = ft_strjoin(list->content, tmp);
		free(lstcontent);
		if (ft_strchr(tmp, '\n'))
			break ;
	}
	free(tmp);
	if (ret == -1)
		return (-1);
	return (ret);
}

int					get_next_line(const int fd, char **line)
{
	static	t_list	*head;
	t_list			*list;
	char			*newline;
	void			*tmp;

	if (fd < 0 || !line || BUFF_SIZE < 1 || read(fd, *line, 0) < 0)
		return (-1);
	list = get_list(fd, &head);
	if (fill_buffer(fd, list) == -1 || list->content == NULL)
		return (-1);
	if (!(newline = ft_strchr(list->content, '\n')))
	{
		*line = ft_strdup(list->content);
		tmp = list->content;
		list->content = ft_strnew(0);
		free(tmp);
		return (ft_strlen(*line) ? 1 : 0);
	}
	*line = ft_strsub(list->content, 0, newline - (char *)list->content);
	tmp = list->content;
	list->content = ft_strdup(newline + 1);
	free(tmp);
	return (newline ? 1 : 0);
}
