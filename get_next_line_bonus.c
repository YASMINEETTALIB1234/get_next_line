/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettalib <yettalib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 21:22:15 by yettalib          #+#    #+#             */
/*   Updated: 2024/12/11 21:27:58 by yettalib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_extract(char **buffer)
{
	size_t	i;
	size_t	j;
	char	*line;
	size_t	additional_size;

	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	additional_size = 0;
	if ((*buffer)[i] == '\n')
		additional_size = 1;
	line = (char *)malloc(i + 1 + additional_size);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = (*buffer)[j];
		j++;
	}
	if ((*buffer)[i] == '\n')
		line[j++] = '\n';
	line[j] = '\0';
	return (line);
}

static void	next_buffer(char **buffer)
{
	size_t	i;
	size_t	j;
	char	*new_buffer;

	i = 0;
	j = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	if ((*buffer)[i] == '\0')
		(free(*buffer), *buffer = NULL);
	else
	{
		new_buffer = malloc(ft_strlen(*buffer) - i + 1);
		if (!new_buffer)
		{
			free(*buffer);
			*buffer = NULL;
			return ;
		}
		i++;
		while ((*buffer)[i])
			new_buffer[j++] = (*buffer)[i++];
		new_buffer[j] = '\0';
		(free(*buffer), *buffer = new_buffer);
	}
}

static int	append_to_buffer(int fd, char **buffer)
{
	char	temp_buffer[BUFFER_SIZE + 1];
	int		bytes_read;

	while (1)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (-1);
		if (bytes_read == 0)
			break ;
		temp_buffer[bytes_read] = '\0';
		*buffer = ft_strjoin(*buffer, temp_buffer);
		if (!(*buffer))
			return (-1);
		if (ft_strchr(*buffer, '\n'))
			break ;
	}
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*buffers[OPEN_MAX];
	char		*line;
	int			result;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (NULL);
	result = append_to_buffer(fd, &buffers[fd]);
	if (result < 0)
		return (free(buffers[fd]), buffers[fd] = NULL, NULL);
	if (!buffers[fd] || buffers[fd][0] == '\0')
		return (free(buffers[fd]), buffers[fd] = NULL, NULL);
	line = ft_extract(&buffers[fd]);
	if (!line)
		return (free(buffers[fd]), buffers[fd] = NULL, NULL);
	next_buffer(&buffers[fd]);
	if (line[0] == '\0' && !buffers[fd])
		return (free(line), NULL);
	return (line);
}
