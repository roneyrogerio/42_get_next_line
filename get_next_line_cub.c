/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_cub.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-oliv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 09:34:55 by rde-oliv          #+#    #+#             */
/*   Updated: 2020/04/24 12:42:45 by rde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*lst_new(t_pseudo_fd *pfd)
{
	size_t	i;
	size_t	size;
	t_list	*el;

	size = pfd->i - pfd->offset;
	if (pfd->buf[pfd->i] != '\n')
		size += 1;
	if (!(el = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (!(el->str = (char *)malloc(size + 1)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		el->str[i] = pfd->buf[i + pfd->offset];
		i++;
	}
	el->str[i] = '\0';
	pfd->list_linelen += size;
	el->next = NULL;
	return (el);
}

int		markup(t_pseudo_fd *pfd)
{
	t_list	*ptr;

	pfd->i = pfd->offset;
	while (pfd->i < pfd->size)
	{
		if (pfd->buf[pfd->i] == '\n' || pfd->i == pfd->size - 1)
		{
			if (!(ptr = lst_new(pfd)))
				return (0);
			if (!pfd->line_liststart)
				pfd->line_liststart = ptr;
			else
				pfd->line_listlast->next = ptr;
			pfd->line_listlast = ptr;
			pfd->offset = pfd->i + 1;
			if (pfd->buf[pfd->i] == '\n')
				pfd->list_hasline = 1;
			break ;
		}
		pfd->i++;
	}
	return (1);
}

int		list2line(t_pseudo_fd *pfd, char **line)
{
	int		i;
	int		j;
	int		ret;
	t_list	*ptr;

	j = 0;
	ret = pfd->list_linelen;
	if (ret && !(*line = (char *)malloc(pfd->list_linelen + 1)))
		return (-1);
	if (ret)
		(*line)[pfd->list_linelen] = '\0';
	while (pfd->line_liststart)
	{
		i = 0;
		while (ret && pfd->line_liststart && pfd->line_liststart->str[i])
			(*line)[j++] = pfd->line_liststart->str[i++];
		free(pfd->line_liststart->str);
		ptr = pfd->line_liststart->next;
		free(pfd->line_liststart);
		pfd->line_liststart = ptr;
	}
	pfd->list_linelen = 0;
	pfd->list_hasline = 0;
	pfd->line_listlast = NULL;
	return (ret ? ret : -1);
}

int		get_next_line(int fd, char **line)
{
	static t_pseudo_fd	pfd;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (pfd.size && pfd.offset <= pfd.size && !pfd.list_hasline)
		if (!markup(&pfd))
			return (-1);
	while (!pfd.list_hasline)
	{
		pfd.size = read(fd, pfd.buf, BUFFER_SIZE);
		if (pfd.size < 0)
			return (-1);
		if (pfd.size == 0)
			break ;
		pfd.offset = 0;
		if (!markup(&pfd))
			return (-1);
	}
	return (list2line(&pfd, line));
}
