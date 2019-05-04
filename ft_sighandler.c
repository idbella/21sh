/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sighandler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 19:01:47 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/04 21:10:35 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"
#include "term_cap/line_edit.h"

void	ft_norm(t_tcline *line, t_tc *list)
{
	t_tcline		*head;

	head = line;
	while (line->prev)
	{
		head = line;
		line = line->prev;
	}
	ft_print_path(&params);
	while (head)
	{
		movecursor(list, 0, list->y + 1);
		ft_putstr(head->line);
		movecursor(list, list->x + head->len % list->sw,
			list->y + head->len / list->sw);
		head->cursor = head->len;
		*(params.pline) = head;
		head = head->next;
	}
}

void	ft_sig_win_handler(int sig_num)
{
	t_tc			*list;
	t_tcline		*line;
	struct winsize	size;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	(void)sig_num;
	list = *(params.ptermcap);
	line = *(params.pline);
	(*(params.ptermcap))->sh = size.ws_row;
	(*(params.ptermcap))->sw = size.ws_col;
	list->x = 0;
	list->y = 0;
	tputs(tgetstr("cl", NULL), 1, ft_putcharc);
	ft_norm(line, list);
}

void	ft_sig_int_handler(int sig)
{
	if (!params.waiting)
	{
		params.ctrlc = 1;
		goend(*(params.ptermcap), params.pline);
		movecursor(*(params.ptermcap), 0, (*(params.ptermcap))->y + 1);
		if (sig == SIGINT)
			ft_print_path(&params);
		(*(params.pline))->line = 0;
		(*(params.pline))->cursor = 0;
		(*(params.pline))->len = 0;
		(*(params.pline))->prev = 0;
		(*(params.pline))->next = 0;
		getxy(*(params.ptermcap));
	}
}
