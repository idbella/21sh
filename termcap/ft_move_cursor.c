/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_cursor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:13:43 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/26 11:18:02 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

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
