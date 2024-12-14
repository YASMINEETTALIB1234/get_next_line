/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yettalib <yettalib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 20:42:01 by yettalib          #+#    #+#             */
/*   Updated: 2024/12/11 20:42:02 by yettalib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strchr(char *s, int ch)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == ch)
			return (1);
		s++;
	}
	return (0);
}

char	*join(char *d, char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1 && s1[i])
	{
		d[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		d[i + j] = s2[j];
		j++;
	}
	d[i + j] = '\0';
	return (d);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ch;

	if (!s1)
	{
		s1 = malloc(sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (free(s1), s1 = NULL, NULL);
	ch = (char *)malloc(1 + ft_strlen(s1) + ft_strlen(s2));
	if (!ch)
		return (free(s1), s1 = NULL, NULL);
	ch = join(ch, s1, s2);
	free(s1);
	s1 = NULL;
	return (ch);
}
