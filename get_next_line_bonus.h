/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rde-oliv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 10:53:05 by rde-oliv          #+#    #+#             */
/*   Updated: 2020/04/16 11:36:32 by rde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

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
