/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassnao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 18:16:56 by amassnao          #+#    #+#             */
/*   Updated: 2019/05/01 18:25:22 by amassnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

void	addtohistory(t_params *list, char *cmd)
{
	t_list *new;

	if (list->history != NULL)
		if (!ft_strcmp(cmd, (char *)list->history->content))
			return ;
	new = (t_list *)malloc(sizeof(t_list));
	new->content = (void *)ft_strdup(cmd);
	if (list->history == NULL)
		new->content_size = 0;
	else
		new->content_size = (int)list->history->content_size + 1;
	new->next = list->history;
	list->history = new;
}

void	movetobegin(t_tc *list, t_tcline *line)
{
	t_tcline	*tmpline;
	int			dx;
	int			dy;

	dx = line->cursor % list->sw;
	dy = line->cursor / list->sw;
	tmpline = line->prev;
	while (tmpline)
	{
		dy += tmpline->len / list->sw;
		if (tmpline->len % list->sw && tmpline != line)
			dy += 1;
		tmpline = tmpline->prev;
	}
	movecursor(list, list->x - dx, list->y - dy);
}

void	history_up(t_tc *list, t_tcline **line, t_params *params)
{
	int		i;
	t_list	*history;

	history = params->history;
	if (!history)
		return ;
	if (list->khistory == (int)history->content_size)
		return ;
	i = 0;
	(list->khistory < (int)history->content_size) ? list->khistory++ : 0;
	while (history)
	{
		if (i++ == list->khistory)
		{
			movetobegin(list, *line);
			tputs(tgetstr("cd", NULL), 1, ft_putcharc);
			*line = setlines((char *)history->content);
			putlines(list, line);
			break ;
		}
		history = history->next;
	}
}

void	reset_line(t_tc *list, t_tcline **line)
{
	movetobegin(list, *line);
	tputs(tgetstr("cd", NULL), 1, ft_putcharc);
	(*line)->line = NULL;
	(*line)->len = 0;
	(*line)->cursor = 0;
	(*line)->prev = NULL;
	(*line)->next = NULL;
}

void	history_down(t_tc *list, t_tcline **line, t_params *params)
{
	int		i;
	t_list	*history;

	history = params->history;
	if (list->khistory <= 0 || !history)
	{
		(list->khistory == 0) ? list->khistory-- : 0;
		return (reset_line(list, line));
	}
	(list->khistory > 0) ? list->khistory-- : 0;
	i = 0;
	while (history)
	{
		if (i++ == list->khistory)
		{
			movetobegin(list, *line);
			tputs(tgetstr("cd", NULL), 1, ft_putcharc);
			*line = setlines((char *)history->content);
			putlines(list, line);
			break ;
		}
		history = history->next;
	}
}
