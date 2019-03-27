/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 02:54:15 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/27 21:41:32 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../ft_21sh.h"

int		ft_get_cline(t_line *line)
{
	int len;
	int	c_line;
	int width;

	width	= ft_get_width();
	len		= ft_strlen(line->data) + ft_strlen(line->prefix);
	c_line	= (len - line->cursor) / width + 1;
	return (c_line);
}

int		ft_get_nline(t_line *line)
{
	int width;
	int len;
	int	n_line;

	width	= ft_get_width();
	len		= ft_strlen(line->data) + ft_strlen(line->prefix);
	n_line	= len / width + 1;
	return (n_line);
}

int		ft_cloumn(t_line *line)
{
	int width;
	int	c_column;
	int len;

	len			= ft_strlen(line->data) + ft_strlen(line->prefix);
	width		= ft_get_width();
	c_column	= (len - line->cursor) % width;
	return (c_column);
}



int	ft_get_width()
{
	struct winsize size;
	ioctl(0, TIOCGWINSZ, &size);
	return (size.ws_col);
}

int	ft_put(int c)
{
	ft_putchar_fd(c, 0);
	return (c);
}

void	ft_backspace(t_line *line)
{
	int		len;
	int		index;

	len = ft_strlen(line->data);
	if (len)
	{
		index = len - line->cursor - 1;
		if (index >= 0)
			line->data = ft_delchar(&line->data, index);
	}
}

void	ft_next_word(t_line *line)
{
	int i;
	int start;

	i = ft_strlen(line->data) - line->cursor;
	start = 0;
	while (line->data[i])
	{
		if (ft_isspace(line->data[i]))
			start = 1;
		else if (start)
		{
			line->cursor = ft_strlen(line->data) - i;
			break;
		}
		i++;
	}
}

void	ft_previous_word(t_line *line)
{
	int i;
	int start;

	i = ft_strlen(line->data) - line->cursor - 1;
	start = 0;
	while (i >= 0)
	{
		if (!ft_isspace(line->data[i]) && i > 0 && ft_isspace(line->data[i - 1]))
			break;
		i--;
	}
	if (i < 0)
		i = 0;
	line->cursor = ft_strlen(line->data) - i;
}

void	ft_init(t_line *line)
{
	line->c = 0;
	line->clipboard = NULL;
	line->select_mode = 0;
	line->select_start = 0;
	line->data = ft_strnew(0);
	line->cursor = 0;
}

static char	ft_isqoute(char *str)
{
	int	index;
	int qoutes;
	int	dqouts;

	index = 0;
	qoutes = 0;
	dqouts = 0;
	while (str[index])
	{
		if (!(qoutes % 2) && str[index] == '\"')
			dqouts++;
		else if (!(dqouts % 2) && str[index] == '\'')
			qoutes++;
		index++;
	}
	if (dqouts % 2)
		return ('\"');
	if (qoutes % 2)
		return ('\'');
	return (0);
}

void	ft_get_len(t_line *line)
{
	t_list *list;

	list = line->old_lines;
	while (list)
	{

		list = list->next;
	}
}

char *ft_getline(t_line *line)
{
	int		len;
	char	c[2];

	ft_putstr_fd(line->prefix, 0);
	ft_init(line);
	while(read(0, &line->c, 3))
	{
		ft_clearline(line);
		if (line->c == '\n')
		{
			ft_isqoute(line->data);
			ft_print(line);
			ft_putchar('\n');
			return (line->data);
		}
		ft_special_keys(line);
		if (ft_isprint(line->c))
		{
			len = ft_strlen(line->data) - line->cursor;
			if (len >= 0)
			{
				c[0] = line->c;
				c[1] = '\0';
				line->data = ft_insert_str(line->data, c, ft_strlen(line->data) - line->cursor);
			}
		}
		ft_print(line);
		line->c = 0;
	}
	return (0);
}
