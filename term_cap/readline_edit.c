/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_edit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassnao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 18:26:51 by amassnao          #+#    #+#             */
/*   Updated: 2019/05/01 18:28:57 by amassnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

void	selectext(t_tc *list, t_tcline **line)
{
	if ((*line)->cursor >= (*line)->len)
		return ;
	(list->sitext == list->setext) ? list->sitext = (*line)->cursor : 0;
	list->setext = (*line)->cursor + 1;
	tputs(tgetstr("mr", NULL), 1, ft_putcharc);
	write(1, (*line)->line + ((*line)->cursor), 1);
	tputs(tgetstr("me", NULL), 1, ft_putcharc);
	tputs(tgetstr("le", NULL), 1, ft_putcharc);
	right(list, line);
}

void	reverselectext(t_tc *list, t_tcline **line)
{
	if (list->sitext == -1)
		return ;
	list->setext = (*line)->cursor - 1;
	if (list->setext < list->sitext)
	{
		list->setext = -1;
		list->sitext = -1;
		return ;
	}
	left(list, line);
	write(1, (*line)->line + ((*line)->cursor), 1);
	((list->x + 1) % list->sw) ? tputs(tgetstr("le", NULL), 1, ft_putcharc) : 0;
}

void	copy(t_tc *list, t_tcline **line, int mode)
{
	int si;
	int se;

	if (list->sitext == -1)
		return ;
	if (list->text)
		free(list->text);
	si = list->sitext;
	se = list->setext;
	list->text = ft_strsub((*line)->line, list->sitext,
			list->setext - list->sitext);
	clearselect(list, line);
	if (mode)
		while (si < se)
		{
			deletchar(list, line, "O");
			si++;
		}
}

void	past(t_tc *list, t_tcline *line)
{
	char *text;

	if (!list->text)
		return ;
	text = list->text;
	ft_puttext(list, line, text++);
}

void	clearselect(t_tc *list, t_tcline **line)
{
	int dx;

	if (list->sitext == -1)
		return ;
	dx = list->setext - list->sitext;
	while (list->setext != -1)
		reverselectext(list, line);
	movecursor(list, list->x + dx % list->sw, list->y + dx / list->sw);
	(*line)->cursor += dx;
}
