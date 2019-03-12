/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 06:27:37 by sid-bell          #+#    #+#             */
/*   Updated: 2019/02/18 15:45:05 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static ssize_t	ft_endl(char *str)
{
	ssize_t pos;

	pos = 0;
	while (*str)
	{
		if (*str == '\n')
			return (pos);
		str++;
		pos++;
	}
	return (-1);
}

static int		ft_adjust(char **line, char **array, int pos)
{
	if (pos >= 0)
	{
		*line = ft_strsub(*array, 0, pos);
		*array = *array + pos + 1;
	}
	else
	{
		*line = *array;
		if (!**array)
		{
			*line = NULL;
			return (0);
		}
		*array = NULL;
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static char *array[4864];
	ssize_t		lenght;
	ssize_t		pos;
	char		buff_test[1];

	if (fd < 0 || !line || fd > 4863 || read(fd, buff_test, 0) < 0)
		return (-1);
	if (!array[fd])
		if (!(array[fd] = ft_strnew(1)))
			return (-1);
	if ((pos = ft_endl(array[fd])) == -1)
	{
		if (!(*line = ft_strnew(BUFF_SIZE)))
			return (-1);
		while ((lenght = read(fd, *line, BUFF_SIZE)) > 0)
		{
			(*line)[lenght] = '\0';
			array[fd] = ft_strjoin(array[fd], *line);
			if ((pos = ft_endl(array[fd])) >= 0)
				break ;
		}
		if (lenght < 0)
			return (-1);
	}
	return (ft_adjust(line, &array[fd], pos));
}
