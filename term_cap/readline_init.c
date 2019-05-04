/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassnao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 18:35:24 by amassnao          #+#    #+#             */
/*   Updated: 2019/05/01 18:48:28 by amassnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

int			ft_putcharc(int c)
{
	char ch;

	ch = c;
	return (write(1, &ch, 1));
}

void		rawmode(t_tc *list)
{
	struct termios termf;
	struct termios termi;

	tcgetattr(0, &termi);
	tcgetattr(0, &termf);
	termf.c_lflag &= ~(ECHO | ECHONL | ICANON);
	termf.c_cc[VMIN] = 1;
	termf.c_cc[VTIME] = 0;
	tcsetattr(0, TCSAFLUSH, &termf);
	list->termi = termi;
}

void		getxy(t_tc *list)
{
	char	pos;
	int		i;
	char	buffer[20];
	char	**ret;

	write(1, "\033[6n", 4);
	pos = 0;
	i = 0;
	while (pos != 'R')
	{
		read(0, &pos, 1);
		buffer[i++] = pos;
	}
	ret = ft_strsplit(buffer + 1, ';');
	list->x = ft_atoi(ret[1]) - 1;
	list->y = ft_atoi(ret[0] + 1) - 1;
	free(ret[0]);
	free(ret[1]);
	free(ret);
}

t_tc		*init(void)
{
	t_tc			*list;
	struct winsize	size;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	if (tgetent(NULL, getenv("TERM")) == ERR)
		return (NULL);
	list = (t_tc *)malloc(sizeof(t_tc));
	list->text = NULL;
	list->sw = size.ws_col;
	list->sh = size.ws_row;
	list->sitext = -1;
	list->setext = -1;
	list->khistory = -1;
	list->history = NULL;
	rawmode(list);
	getxy(list);
	return (list);
}

t_tcline	*setlines(char *content)
{
	char		**line;
	int			i;
	t_tcline	*tclines;
	t_tcline	*htclines;

	i = 0;
	line = (content) ? ft_strsplit(content, '\n') : NULL;
	(line) ? tclines = (t_tcline *)malloc(sizeof(t_tcline)) : 0;
	(line) ? tclines->prev = NULL : NULL;
	htclines = (line) ? tclines : NULL;
	if (line)
		while (line[i])
		{
			tclines->line = line[i];
			tclines->len = ft_strlen(line[i]);
			if (line[++i])
			{
				tclines->next = (t_tcline *)malloc(sizeof(t_tcline));
				tclines->next->prev = tclines;
			}
			else
				tclines->next = NULL;
			tclines = tclines->next;
		}
	return (htclines);
}
