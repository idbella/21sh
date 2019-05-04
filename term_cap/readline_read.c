/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassnao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 19:18:52 by amassnao          #+#    #+#             */
/*   Updated: 2019/05/01 19:18:55 by amassnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

char		*joinchar(char **base, char extend, int index, int mode)
{
	char	*result;
	char	*tmp;
	int		i;
	int		j;

	tmp = *base;
	result = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + 2));
	i = 0;
	if (mode == 0)
	{
		if (tmp)
			while (tmp[i])
			{
				result[i] = tmp[i];
				i++;
			}
		result[i++] = extend;
	}
	else if (mode == 1)
	{
		j = 0;
		while (tmp[i] && i < index)
			result[j++] = tmp[i++];
		result[j++] = extend;
		while (tmp[i])
			result[j++] = tmp[i++];
		i = j;
	}
	else if (mode == 2)
	{
		while (tmp[i] && tmp[i + 1])
		{
			result[i] = tmp[i];
			i++;
		}
	}
	else if (mode == 3)
	{
		j = 0;
		while (tmp[i] && i < index)
			result[j++] = tmp[i++];
		i++;
		while (tmp[i])
			result[j++] = tmp[i++];
		i = j;
	}
	result[i] = '\0';
	free(*base);
	return (result);
}

char		*read_setup(t_params *params)
{
	t_tc		*list;
	t_tcline	*tclines;

	list = init();
	if (!list)
		return (NULL);
	tclines = (t_tcline *)malloc(sizeof(t_tcline));
	tclines->line = NULL;
	tclines->cursor = 0;
	tclines->len = 0;
	tclines->next = NULL;
	tclines->prev = NULL;
	params->ptermcap = &list;
	params->pline = &tclines;
	read_key(list, &tclines, params);
	tcsetattr(0, TCSANOW, &list->termi);
	free(list);
	return (migratelines(tclines));
}

int			ft_iskey(char *buffer, int key, int kkey, int kkkey)
{
	if (buffer[0] == key &&
			buffer[1] == kkey &&
			buffer[2] == kkkey)
		return (1);
	return (0);
}

t_tcline	*ft_puttext(t_tc *list, t_tcline *line, char *buffer)
{
	t_tcline	*new;

	if (buffer[0] == 10)
	{
		if (line->next == NULL)
		{
			new = (t_tcline *)malloc(sizeof(t_tcline));
			new->cursor = 0;
			new->next = NULL;
			new->prev = line;
			line->next = new;
			new->line = ft_strdup(line->line + line->cursor);
			new->len = ft_strlen(line->line + line->cursor);
			line->line = ft_strsub(line->line, 0, line->cursor);
			line->len = line->cursor;
			line->cursor = 0;
			tputs(tgetstr("cd", NULL), 1, ft_putcharc);
			movecursor(list, 0, list->y + 1);
			(list->y + 1 > list->sh - 1) ? list->y = list->sh - 1 : 0;
			line = new;
		}
		else
		{
			line->cursor = 0;
			movecursor(list, 0, list->y + 1);
			(list->y + 1 > list->sh - 1) ? list->y = list->sh - 1 : 0;
			line = line->next;
			line->cursor = 0;
		}
		return (*(buffer + 1)) ? ft_puttext(list, line, buffer + 1) : line;
	}
	if (line->cursor < line->len)
		line->line = joinchar(&line->line, buffer[0], line->cursor, 1);
	else
		line->line = joinchar(&line->line, buffer[0], line->cursor, 0);
	tputs(tgetstr("im", NULL), 1, ft_putcharc);
	tputs(tgetstr("ic", NULL), 1, ft_putcharc);
	write(1, buffer, 1);
	tputs(tgetstr("ei", NULL), 1, ft_putcharc);
	list->x++;
	line->cursor++;
	line->len++;
	if (line->cursor % list->sw == 0 && line->cursor)
	{
		list->x = 0;
		list->y++;
	}
	(line->cursor < line->len) ? ft_putstr(line->line + line->cursor) : 0;
	fixlines(list, line);
	if ((ft_isprint(buffer[1]) || buffer[1] == 10) && buffer[1])
		return (ft_puttext(list, line, buffer + 1));
	return (line);
}

void		read_key(t_tc *list, t_tcline **line, t_params *params)
{
	char	buffer[7];
	int		i;

	i = 0;
	ft_memset(buffer, 0, 7);
	while (read(0, &buffer, 6) > 0)
	{
		if (!ft_iskey(buffer, -61, -89, 0) && !ft_iskey(buffer, -30, -119, -91)
				&& !ft_iskey(buffer, -30, -119, -92) && !ft_iskey(buffer, -30, -119, -120))
			clearselect(list, line);
		if (ft_iskey(buffer, 10, 0, 0))
			return (gotoend(list, line));
		else if (ft_iskey(buffer, 4, 0, 0))
		{
			if (!(*line)->next && !(*line)->prev
					&& !(*line)->len && !params->heredoc && !params->quate)
				exit(0);
			else if (params->heredoc == 1 && !(*line)->len && !params->quate)
			{
				(*line)->line = 0;
				(*line)->len = 0;
				(*line)->cursor = 0;
				return (gotoend(list, line));
			}
		}
		else if (ft_iskey(buffer, 9, 0, 0))
			(void)1;//completecmd(list, *line);
		else if (ft_iskey(buffer, 27, 91, 67))
			right(list, line);
		else if (ft_iskey(buffer, 27, 91, 68))
			left(list, line);
		else if (ft_iskey(buffer, 27, 91, 65))
			history_up(list, line, params);
		else if (ft_iskey(buffer, 27, 91, 66))
			history_down(list, line, params);
		else if (ft_iskey(buffer, 27, 91, 72))
			gobegin(list, line);
		else if (ft_iskey(buffer, 27, 91, 70))
			goend(list, line);
		else if (ft_iskey(buffer, -30, -119, -91))
			selectext(list, line);
		else if (ft_iskey(buffer, -30, -119, -92))
			reverselectext(list, line);
		else if (ft_iskey(buffer, -61, -89, 0))
			copy(list, line, 0);
		else if (ft_iskey(buffer, -30, -119, -120))
			copy(list, line, 1);
		else if (ft_iskey(buffer, -30, -120, -102))
			past(list, *line);
		else if (ft_iskey(buffer, 127, 0, 0))
			deletchar(list, line, buffer);
		else if (ft_iskey(buffer, 27, 27, 91))
		{
			if (ft_iskey(buffer + 3, 65, 0, 0))
				prevline(list, line);
			else if (ft_iskey(buffer + 3, 66, 0, 0))
				nextline(list, line);
			else if (ft_iskey(buffer + 3, 67, 0, 0))
				nextword(list, line);
			else if (ft_iskey(buffer + 3, 68, 0, 0))
				previewword(list, line);
		}
		else
			*line = ft_puttext(list, *line, buffer);
		ft_memset(buffer, 0, 7);
	}
}
