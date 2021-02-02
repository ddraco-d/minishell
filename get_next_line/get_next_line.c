/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddraco <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 13:44:08 by ddraco            #+#    #+#             */
/*   Updated: 2020/12/31 12:57:11 by ddraco           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char			*rem_ch(char **rem, char **line)
{
	char		*p;

	p = NULL;
	if (*rem)
	{
		if ((p = ft_strchr(*rem, '\n')))
		{
			*p = '\0';
			*line = ft_strdup(*rem);
			p++;
			ft_strcpy(*rem, p);
		}
		else
		{
			*line = ft_strdup(*rem);
			free(*rem);
			*rem = NULL;
		}
	}
	else
		*line = ft_strdup("");
	return (p);
}

char			*valid(char **line, size_t size, int fd)
{
	char		*buf;

	buf = NULL;
	if (size < 1 || fd < 0 || !line)
		return (NULL);
	if (!(buf = (char*)malloc(size + 1)))
		return (NULL);
	if (read(fd, buf, 0) < 0)
	{
		free(buf);
		return (NULL);
	}
	else
		return (buf);
}

void			search_n(char **p, char **buf, char **rem)
{
	if ((*p = ft_strchr(*buf, '\n')))
	{
		*(*p) = '\0';
		free(*rem);
		*rem = ft_strdup(++(*p));
	}
}

int				get_next_line(int fd, char **line)
{
	int			was_read;
	static char	*rem;
	char		*buf;
	char		*p;
	char		*tmp;

	if (!(buf = valid(line, BUFFER_SIZE, fd)))
		return (-1);
	p = rem_ch(&rem, line);
	while ((!p && (was_read = (int)read(fd, buf, BUFFER_SIZE))) \
	|| ((ft_strcmp(*line, "") != 0) && (was_read == 0)))
	{
		buf[was_read] = '\0';
		search_n(&p, &buf, &rem);
		tmp = *line;
		if (!(*line = ft_strjoin(*line, buf)) || was_read < 0)
			return (-1);
		free(tmp);
	}
	free(buf);
	if (was_read == 0)
		return (-2);
	return (p) ? 1 : 0;
}
