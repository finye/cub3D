/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaine <eelaine@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:37:46 by eelaine           #+#    #+#             */
/*   Updated: 2024/08/28 15:06:45 by eelaine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/get_next_line.h"

static void	ft_free(void **s)
{
	if (s && *s)
	{
		free(*s);
		*s = NULL;
	}
}

static char	*fill_stash(int fd, char *stash, char *buf)
{
	char	*tmp;
	ssize_t	buf_read;

	buf_read = 1;
	while (buf_read != 0)
	{
		buf_read = read(fd, buf, BUFFER_SIZE);
		if (buf_read == -1)
		{
			ft_free((void **)&stash);
			return (NULL);
		}
		else if (buf_read == 0)
			break ;
		buf[buf_read] = 0;
		tmp = stash;
		stash = ft_strjoin_gnl(tmp, buf);
		ft_free((void **)&tmp);
		if (ft_strchr_gnl(buf, '\n'))
			break ;
	}
	return (stash);
}

static char	*next_line(char **line)
{
	char	*stash;
	char	*res;
	ssize_t	i;

	i = 0;
	while ((*line)[i] != '\0' && (*line)[i] != '\n')
		i++;
	if ((*line)[i] == '\0' || (*line)[i + 1] == '\0')
		return (NULL);
	stash = ft_substr_gnl(*line, i + 1, ft_strlen_gnl(*line) - i - 1);
	if (stash == 0)
	{
		ft_free((void **)&(*line));
		return (NULL);
	}
	res = *line;
	*line = ft_substr_gnl(*line, 0, i + 1);
	if (!*line)
	{
		ft_free((void **)&res);
		ft_free((void **)&stash);
		return (NULL);
	}
	ft_free((void **)&res);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		buf[BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (stash)
	{
		line = ft_strjoin_gnl(line, stash);
		ft_free((void **)&stash);
	}
	line = fill_stash(fd, line, buf);
	if (!line)
		return (NULL);
	stash = next_line(&line);
	return (line);
}
