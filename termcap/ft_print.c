/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:18:31 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/26 23:08:51 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

void ft_print(t_line *line)
{
	int len;
	int pos;
	int width;
	int c_line;
	int n_line;

	ft_putstr_fd(line->prefix, 0);
	if (line->select_mode)
		ft_select(line);
	else
		ft_putstr_fd(line->data, 0);
	len = ft_strlen(line->data) + ft_strlen(line->prefix);
	width = ft_get_width();
	n_line = ft_get_cline(line);
	c_line = ft_get_nline(line);
	pos = len - line->cursor;
	if (n_line == c_line && ft_isprint(line->c) && !line->cursor && pos % width == 0)
	{
		tputs(line->mv_down, 1, ft_put);
		ft_putchar_fd('\r', 0);
	}
	ft_move_cursor(line);
}
