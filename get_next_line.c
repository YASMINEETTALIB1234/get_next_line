/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettalib <yettalib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 20:24:51 by yettalib          #+#    #+#             */
/*   Updated: 2024/12/12 15:57:58 by yettalib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

int	append_to_buffer(int fd, char **buffer)
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
	static char	*buffer = NULL;
	char		*line;
	int			result;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	result = append_to_buffer(fd, &buffer);
	if (result < 0)
		return (free(buffer), buffer = NULL, NULL);
	if (!buffer || buffer[0] == '\0')
		return (free(buffer), buffer = NULL, NULL);
	line = ft_extract(&buffer);
	if (!line)
		return (free(buffer), buffer = NULL, NULL);
	next_buffer(&buffer);
	if (line[0] == '\0' && !buffer)
		return (free(line), NULL);
	return (line);
}
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd = open("test.txt", O_RDONLY);
	char	*line;

	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}