/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-oliv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 15:48:16 by rde-oliv          #+#    #+#             */
/*   Updated: 2020/04/16 10:03:26 by rde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_list
{
	char			*str;
	int				eol;
	char			*free;
	size_t			len;
	struct s_list	*next;
}				t_list;

typedef struct	s_gnl
{
	char	*buffer;
	int		ret;
	int		eol;
	t_list	*list;
	t_list	*last;
}				t_gnl;

int				get_next_line(int fd, char **line);

#endif
