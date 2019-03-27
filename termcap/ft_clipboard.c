/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clipboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:15:15 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/26 21:18:55 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

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
		ft_putchar_fd(line->data[i], 0);
		if (i == end)
			tputs(line->stop_v, 1, ft_put);
		i++;
	}
	tputs(line->stop_v, 1, ft_put);
}

void	ft_cut(t_line *line)
{
	int		start;
	int		end;
	int		c_pos;
	int		len;
	char	*p1;
	char 	*p2;

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
	len  = end - start;
	if (len > 0)
	{
		p1 = ft_strsub(line->data, 0, start);
		line->clipboard = ft_strsub(line->data, start, len + 1);
		p2 = ft_strsub(line->data, end + 1, ft_strlen(line->data) - end);
		line->data = ft_strjoin(p1, p2);
		line->select_mode = 0;
		line->cursor = ft_strlen(p2);
	}
}

void	ft_copy(t_line *line)
{
	int start;
	int end;
	int c_pos;
	int len;

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
	len  = end - start;
	if (len > 0)
		line->clipboard = ft_strsub(line->data, start, len + 1);
	line->select_mode = 0;
}

void	ft_past(t_line *line)
{
	int len;

	if (line->clipboard)
	{
		len = ft_strlen(line->data) - line->cursor;
		line->data = ft_insert_str(line->data, line->clipboard, ft_strlen(line->data) - line->cursor);
	}
}
