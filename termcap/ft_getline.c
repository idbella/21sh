/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 02:54:15 by sid-bell          #+#    #+#             */
/*   Updated: 2019/04/02 20:58:04 by sid-bell         ###   ########.fr       */
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

void	ft_clearline(t_line *line)
{
	int count;
	int	current;
	int i;

	count = ft_get_nline(line);
	current = ft_get_cline(line);
	i = 1;
	while (i < current)
	{
		tputs(line->mv_up, 1, ft_put);	
		i++;
	}
	i = 0;
	while (i < count)
	{
		tputs(line->delete, 1, ft_put);
		ft_putchar('\r');
		i++;
	}
}

void ft_move_cursor(t_line *line)
{
	int width;
	int len;
	int c_line;
	int n_line;
	int c_column;
	int	i;

	len = ft_strlen(line->data) + ft_strlen(line->prefix);
	width = ft_get_width();
	c_line = ft_get_cline(line);
	n_line = ft_get_nline(line);
	c_column = ft_cloumn(line);
	if (len % width == 0 && line->cursor)
		c_line++;
	if (n_line != c_line)
	{
		i = n_line - c_line;
		while (i > 0)
		{
			tputs(line->mv_up, 0, ft_put);
			i--;
		}
	}
	ft_putchar_fd('\r', 0);
	while(c_column > 0)
	{
		tputs(line->mv_right, 0, ft_put);
		c_column--;
	}
}

void	setup(t_line *line, char *prefix)
{
	char	*term;
	char	buff[2048];
	struct	termios termio;

	term = getenv("TERM");	
	tgetent(buff, term);	
	tcgetattr(0, &termio);
	termio.c_lflag = ~ICANON & termio.c_lflag;
	termio.c_lflag = ~ECHO & termio.c_lflag;
	tcsetattr(0, TCSANOW, &termio);
	line->c = 0;
	line->select_mode = 0;
	line->select_start = 0;
	line->data = ft_strnew(0);
	line->prefix = prefix;
	line->cursor = 0;
	line->delete = tgetstr("dl", NULL);
	line->mv_up = tgetstr("up", NULL);
	line->mv_left = tgetstr("le", NULL);
 	line->mv_down = tgetstr("do", NULL);
	line->mv_right = tgetstr("nd", NULL);
	line->reverse_v = tgetstr("mr", NULL);
	line->stop_v = tgetstr("me", NULL);
}

int	ft_get_width()
{
	struct winsize size;

	ioctl(0, TIOCGWINSZ, &size);
	return (size.ws_col);
}

int	ft_put(int c)
{
	ft_putchar(c);
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

void ft_select(t_line *line)
{
	int i;
	int start;
	int end;
	int c_pos;

	c_pos = ft_strlen(line->data) - line->cursor;
	if (c_pos > line->select_start)
	{
		start = line->select_start;
		end = c_pos;
	}
	else
	{
		end = line->select_start;
		start = c_pos;
	}
	i = 0;
	while (line->data[i])
	{
		if (i == start)
			tputs(line->reverse_v, 1, ft_put);
		ft_putchar(line->data[i]);
		if (i == end)
			tputs(line->stop_v, 1, ft_put);
		i++;
	}
	tputs(line->stop_v, 1, ft_put);
}

void ft_print(t_line *line)
{
	int len;
	int pos;
	int width;
	int c_line;
	int n_line;

	ft_putstr(line->prefix);
	if (line->select_mode)
		ft_select(line);
	else
		ft_putstr(line->data);
	len = ft_strlen(line->data) + ft_strlen(line->prefix);
	width = ft_get_width();
	n_line = ft_get_cline(line);
	c_line = ft_get_nline(line);
	pos = len - line->cursor;
	if (n_line == c_line && ft_isprint(line->c) && !line->cursor && pos % width == 0)
	{
		tputs(line->mv_down, 1, ft_put);
		ft_putchar('\r');
	}
	ft_move_cursor(line);
}

void	ft_cursor(t_line *line)
{
	int len;

	len = ft_strlen(line->data);
	if (line->c == C_LEFT)
		line->cursor++;
	else
		line->cursor--;
	if (line->cursor < 0)
		line->cursor = 0;
	if (line->cursor > len)
		line->cursor = len;
}

void	ft_next(t_line *line)
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

void	ft_previous(t_line *line)
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

char	*ft_getline(char *text, char *prefix, t_params *params)
{
	t_line line;

	setup(&line, prefix);
	line.prefix = ft_strdup(prefix);
	ft_putstr_fd(prefix, 0);
	line.data = text ? ft_strdup(text) : ft_strnew(0);
	while(read(0, &line.c, 3))
	{
		ft_clearline(&line);
		ft_special_keys(&line, params);
		if (line.c == '\n')
		{
			line.cursor = 0;
			ft_print(&line);
			ft_putchar('\n');
			params->history_pos = -1;
			return (line.data);
		}
		
		if (ft_isprint(line.c))
		{
			int len = ft_strlen(line.data) - line.cursor;
			if (len >= 0)
			{
				char s[2];
				s[0] = line.c;
				s[1] = '\0';
				line.data = ft_insert_str(line.data, s, ft_strlen(line.data) - line.cursor);
			}
		}
		ft_print(&line);
		line.c = 0;
	}
	return (0);
}
