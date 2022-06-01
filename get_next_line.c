/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarias- <lfarias-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:50:02 by lfarias-          #+#    #+#             */
/*   Updated: 2022/06/01 16:29:40 by lfarias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

t_str_buff	*create_node(void *content, size_t content_size)
{
	t_str_buff	*new_node;

	if (!content)
		return (NULL);
	new_node = malloc(sizeof(t_str_buff));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->start = 0;
	new_node->len = content_size;
	new_node->next = NULL;
	return (new_node);
}

void	add_node(t_str_buff **str_buff, t_str_buff *node)
{
	t_str_buff	*c_node;

	if (!str_buff || !node)
		return ;
	if (!(*str_buff) && node)
	{
		*str_buff = node;
		node->next = NULL;
		return ;
	}
	c_node = *str_buff;
	while (c_node->next)
	{
		c_node = c_node->next;
	}	
	c_node->next = node;
	node->next = NULL;
}

int	copy_to_str(t_str_buff *node, char *str, int str_index, int str_size)
{
	size_t	i;

	i = node->start;
	while (str_index < str_size && i < node->len)
	{
		str[str_index] = node->content[i];
		i++;
		str_index++;
		node->start++;
	}
	return (str_index);
}

char	*get_line(t_str_buff **str_bf, int *lf_count)
{
	char		*new_line;
	t_str_buff	*node;
	size_t		str_size;
	size_t		i;

	str_size = get_strlen(str_bf);
	if (str_size == 0)
		return (NULL);
	new_line = malloc((str_size + 1) * sizeof(char));
	node = *str_bf;
	i = 0;
	while (node != NULL && i < str_size)
	{
		i = copy_to_str(node, new_line, i, str_size);
		if (node->start >= node->len)
			node = next_node(node);
	}
	new_line[str_size] = '\0';
	*lf_count = *lf_count - 1;
	*str_bf = node;
	return (new_line);
}

char	*get_next_line(int fd)
{
	char				*read_bf;
	static t_str_buff	*str_bf;
	static int			lf_count;
	int					bytes_read;

	if (BUFFER_SIZE == 0 || (fd < 0))
		return (NULL);
	bytes_read = -1;
	while (bytes_read != 0)
	{
		if (lf_count > 0)
			break ;
		read_bf = malloc(BUFFER_SIZE);
		bytes_read = read(fd, read_bf, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(read_bf);
			break ;
		}
		add_node(&str_bf, create_node(read_bf, bytes_read));
		lf_count += count_lf(read_bf, bytes_read);
	}
	return (get_line(&str_bf, &lf_count));
}
