/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_lines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassnao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 18:55:00 by amassnao          #+#    #+#             */
/*   Updated: 2019/05/01 18:58:57 by amassnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

void	deletchar(t_tc *list, t_tcline **hline, char *buffer)
{
	t_tcline *line;

	line = *hline;
	if (line->cursor <= 0)
	{
		if (line->prev)
		{
			prevline(list, hline);
			movecursor(list, list->x + (*hline)->len % list->sw,
					list->y + (*hline)->len / list->sw);
			(*hline)->cursor = (*hline)->len;
			deletchar(list, hline, buffer);
		}
		return ;
	}
	line->len--;
	left(list, hline);
	if (line->cursor < line->len)
		line->line = joinchar(&line->line, buffer[0], line->cursor, 3);
	else
		line->line = joinchar(&line->line, buffer[0], line->cursor, 2);
	tputs(tgetstr("cd", NULL), 1, ft_putcharc);
	ft_putstr(line->line + line->cursor);
	if (line->prev && ft_strlen(line->line) == 0)
	{
		line->prev->next = line->next;
		if (line->next)
			line->next->prev = line->prev;
		free(*hline);
		*hline = (*hline)->prev;
		if ((*hline)->len % list->sw || (*hline)->len % list->sw == 0)
			movecursor(list, 0, list->y - (*hline)->len / list->sw - 1);
		else
			movecursor(list, 0, list->y - (*hline)->len / list->sw);
		movecursor(list, list->x + (*hline)->len % list->sw,
				list->y + (*hline)->len / list->sw);
		(*hline)->cursor = (*hline)->len;
	}
	deleteline(list, line);
}

void	putlines(t_tc *list, t_tcline **pline)
{
	t_tcline *line;

	line = *pline;
	while (line)
	{
		ft_putstr(line->line);
		list->x += line->len % list->sw;
		list->y += line->len / list->sw;
		(list->y + 1 > list->sh) ? list->y = list->sh - 1 : 0;
		if (line->next)
			movecursor(list, 0, list->y + 1);
		else
			line->cursor = line->len;
		*pline = line;
		line = line->next;
	}
}

void	prevline(t_tc *list, t_tcline **line)
{
	if (!(*line)->prev)
		return ;
	movecursor(list, list->x - (*line)->cursor % list->sw,
			list->y - (*line)->cursor / list->sw - 1);
	(*line)->prev->cursor = (*line)->cursor;
	*line = (*line)->prev;
	movecursor(list, list->x, list->y - (*line)->len / list->sw);
	((*line)->cursor > (*line)->len) ? (*line)->cursor = (*line)->len : 0;
	movecursor(list, list->x + (*line)->cursor % list->sw,
			list->y + (*line)->cursor / list->sw);
}

void	nextline(t_tc *list, t_tcline **line)
{
	if (!(*line)->next)
		return ;
	movecursor(list, list->x - (*line)->cursor % list->sw,
			list->y - (*line)->cursor / list->sw);
	(*line)->next->cursor = (*line)->cursor;
	movecursor(list, list->x, list->y + (*line)->len / list->sw + 1);
	*line = (*line)->next;
	((*line)->cursor > (*line)->len) ? (*line)->cursor = (*line)->len : 0;
	movecursor(list, list->x + (*line)->cursor % list->sw,
			list->y + (*line)->cursor / list->sw);
}

void	fixlines(t_tc *list, t_tcline *line)
{
	int x;
	int y;
	int dy;

	if (!(line->len % list->sw == 0 && line->len))
		return (movecursor(list, list->x, list->y));
	x = list->x;
	dy = 0;
	movecursor(list, list->x, list->y);
	(list->y > list->sh - 1) ? list->y = list->sh - 1 : 0;
	y = list->y;
	movecursor(list, list->x - line->cursor % list->sw,
			list->y - line->cursor / list->sw);
	movecursor(list, 0, list->y + line->len / list->sw);
	tputs(tgetstr("ce", NULL), 1, ft_putcharc);
	(line->len % list->sw == 0 && line->len
	&& isnespace(list, line) && !line->next) ? y-- : 0;
	line = line->next;
	while (line)
	{
		movecursor(list, 0, list->y + 1);
		tputs(tgetstr("cd", NULL), 1, ft_putcharc);
		ft_putstr(line->line);
		dy = list->y + line->len / list->sw;
		if (line->len % list->sw == 0 && line->len && isnespace(list, line))
			movecursor(list, 0, (dy + 1 > list->sh) ? dy : dy + 1);
		else
			movecursor(list, list->x + line->len % list->sw,
					(dy + 1 > list->sh) ? dy - 1 : dy);
		line = line->next;
	}
	movecursor(list, x, (dy + 1 > list->sh) ? y - 1 : y);
}
