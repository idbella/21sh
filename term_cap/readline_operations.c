/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassnao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 19:10:59 by amassnao          #+#    #+#             */
/*   Updated: 2019/05/01 19:11:01 by amassnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

int		isnespace(t_tc *list, t_tcline *line)
{
	int		dx;
	int		x;
	int		hx;

	dx = line->len - line->cursor;
	hx = (list->sh) * (list->sw - 1);
	x = (dx / (list->sw - 1) + list->y) * (list->sw - 1) +
		((dx % (list->sw - 1)) + list->x);
	return (x >= hx);
}

void	previewword(t_tc *list, t_tcline **line)
{
	int		dx;

	if ((*line)->cursor == 0)
	{
		if (!(*line)->prev)
			return ;
		prevline(list, line);
		movecursor(list, list->x + (*line)->len % list->sw,
				list->y + (*line)->len / list->sw);
		(*line)->cursor = (*line)->len;
		return (previewword(list, line));
	}
	dx = (*line)->cursor;
	(dx == (*line)->len) ? dx-- : 0;
	(!ft_isalnum((*line)->line[dx - 1])) ? dx-- : 0;
	while ((*line)->line[dx] && (*line)->line + dx != (*line)->line)
		if (!ft_isalnum((*line)->line[dx]))
			dx--;
		else
			break ;
	while ((*line)->line[dx] && (*line)->line + dx != (*line)->line)
		if (ft_isalnum((*line)->line[dx]))
			dx--;
		else
			break ;
	(dx) ? dx++ : 0;
	movecursor(list, list->x - ((*line)->cursor % list->sw),
			list->y - ((*line)->cursor / list->sw));
	if (dx == 0)
	{
		if ((*line)->prev && !ft_isalnum((*line)->line[0]))
		{
			(*line)->cursor = 0;
			return (previewword(list, line));
		}
		else if (!ft_isalnum((*line)->line[0]) && (*line)->prev)
			return ;
	}
	movecursor(list, list->x + (dx % list->sw), list->y + (dx / list->sw));
	(*line)->cursor = dx;
}

void	nextword(t_tc *list, t_tcline **line)
{
	int		dx;

	dx = (*line)->cursor;
	while ((*line)->line[dx])
		if (ft_isalnum((*line)->line[dx]))
			dx++;
		else
			break ;
	while ((*line)->line[dx])
		if (!ft_isalnum((*line)->line[dx]))
			dx++;
		else
			break ;
	movecursor(list, list->x - ((*line)->cursor % list->sw),
			list->y - ((*line)->cursor / list->sw));
	movecursor(list, list->x + (dx % list->sw), list->y + (dx / list->sw));
	(*line)->cursor = dx;
	if ((*line)->cursor >= (*line)->len)
	{
		if (!(*line)->next)
			return ;
		nextline(list, line);
		movecursor(list, list->x - (*line)->cursor % list->sw,
				list->y - (*line)->cursor / list->sw);
		(*line)->cursor = 0;
		if (ft_isalnum((*line)->line[0]))
			return ;
		else
			return (nextword(list, line));
	}
}

void	gobegin(t_tc *list, t_tcline **line)
{
	int			dy;
	int			dx;
	t_tcline	*head;

	head = *line;
	dy = head->cursor / list->sw;
	dx = head->cursor % list->sw;
	(!head->prev) ? head->cursor = 0 : 0;
	head = head->prev;
	while (head)
	{
		*line = head;
		dy += head->len / list->sw;
		if (head->len % list->sw)
			dy += 1;
		(!head->prev) ? head->cursor = 0 : 0;
		head = head->prev;
	}
	movecursor(list, list->x - dx, list->y - dy);
}

void	goend(t_tc *list, t_tcline **line)
{
	int			dx;
	int			dy;
	t_tcline	*head;

	head = *line;
	dx = head->cursor % list->sw;
	dy = head->cursor / list->sw;
	movecursor(list, list->x - dx, list->y - dy);
	dx = 0;
	dy = 0;
	if (!head->prev && head->next && ft_strlen(head->line) == 0)
		dy = 1;
	while (head)
	{
		*line = head;
		dy += head->len / list->sw;
		if (head->len % list->sw && head->next)
			dy += 1;
		else if (!head->next)
			dx = head->len % list->sw;
		(!head->next) ? head->cursor = head->len : 0;
		head = head->next;
	}
	movecursor(list, list->x + dx, list->y + dy);
}
