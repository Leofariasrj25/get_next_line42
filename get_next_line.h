/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:09:09 by lfarias-          #+#    #+#             */
/*   Updated: 2022/05/31 19:22:38 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

# define LF '\n'
# define EOS '\0'

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000000
# endif

typedef struct s_str_buffer
{
	char				*content;
	size_t				start;
	size_t				len;
	struct s_str_buffer	*next;
}	t_str_buff;

char		*get_next_line(int fd);
t_str_buff	*create_node(void *content, size_t size);
void		add_node(t_str_buff **str_bf, t_str_buff *node);
int			get_strlen(t_str_buff **str_bf);
size_t		count_lf(char *read_bf, size_t bytes_read);
#endif
