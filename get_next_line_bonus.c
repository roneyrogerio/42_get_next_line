/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-oliv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 10:46:10 by rde-oliv          #+#    #+#             */
/*   Updated: 2020/04/16 14:53:13 by rde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*lst_new(char *str, unsigned int eol, char *free, size_t len)
{
	t_list	*el;

	el = (t_list *)malloc(sizeof(t_list));
	el->str = str;
	el->eol = eol;
	el->free = free;
	el->len = len;
	el->next = NULL;
	return (el);
}

int		parser(t_gnl *v)
{
	size_t	i;
	size_t	start;

	i = 0;
	start = 0;
	v->eol = 0;
	while (i < (size_t)v->ret)
	{
		if (v->last->free[i] == '\n' && (v->eol += 1))
		{
			v->last->next = lst_new(&v->last->free[i + 1], 0, v->last->free, 0);
			v->last->len = i - start;
			v->last->eol = 1;
			v->last->free = NULL;
			v->last = v->last->next;
			start = i + 1;
		}
		i++;
	}
	v->last->len = i - start;
	return (v->eol);
}

int		line_len(t_list *list)
{
	int	len;

	len = 0;
	while (list)
	{
		len += list->len;
		if (list->eol)
			break ;
		list = list->next;
	}
	return (len);
}

int		list2line(t_gnl *v, char **line)
{
	int		i;
	int		j;
	int		eol;
	t_list	*ptr;

	i = 0;
	*line = (char *)malloc(line_len(v->list) + 1);
	while (v->list && !(j = 0))
	{
		while (v->list->len--)
			(*line)[i++] = v->list->str[j++];
		if (v->list->free)
			free(v->list->free);
		ptr = v->list->next;
		eol = v->list->eol;
		free(v->list);
		v->list = ptr;
		if (eol)
			v->eol -= 1;
		if (eol)
			break ;
	}
	(*line)[i] = 0;
	return (v->list ? 1 : 0);
}

int		get_next_line(int fd, char **line)
{
	static t_gnl	y[OPEN_MAX];
	t_gnl			*v;

	v = &y[fd];
	//*line = NULL;
	while (!v->eol && fd >= 0 && BUFFER_SIZE > 0)
	{
		if (!(v->buffer = (char *)malloc(BUFFER_SIZE)))
			return (-1);
		if ((v->ret = read(fd, v->buffer, BUFFER_SIZE)) < 1)
			break ;
		if (!v->list)
			v->list = lst_new(v->buffer, 0, v->buffer, v->ret);
		else if (v->last)
			v->last->next = lst_new(v->buffer, 0, v->buffer, v->ret);
		v->last = (v->last ? v->last->next : v->list);
		if (parser(v))
			break ;
	}
	if (!v->eol && v->buffer && v->ret < 1)
		free(v->buffer);
	if (fd < 0 || BUFFER_SIZE <= 0 || (!v->eol && v->ret < 0))
		return (-1);
	return (list2line(v, line));
}
