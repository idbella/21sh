/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sepcial_keys.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:16:29 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/26 23:55:56 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

void	ft_special_keys(t_line *line)
{

	if (line->c == 127)
		ft_backspace(line);
	if (line->c == SELECT)
	{
		line->select_mode = !line->select_mode;
		line->select_start = ft_strlen(line->data) - line->cursor;
	}
	if (line->c == CUT && line->select_mode)
		ft_cut(line);
	if (line->c == PAST)
		ft_past(line);
	if (line->c == COPY && line->select_mode)
		ft_copy(line);
	if (line->c == END_KEY)
		line->cursor = 0;
	if (line->c == HOME_KEY)
		line->cursor = ft_strlen(line->data);
	if (line->c == NEXT_WORD)
		ft_next_word(line);
	if (line->c == PREVIOUS_WORD)
		ft_previous_word(line);
	if (line->c == C_LEFT || line->c == C_RIGHT)
		ft_cursor(line);
	// if (line->c == UP_LINE)
	// 	line->current_line++;
	// if (line->c == DOWN_LINE)
	// 	line->current_line--;
	// lines_count = ft_lstcount(line->lines);
	// if (line->current_line > lines_count)
	// 	line->current_line = lines_count;
	// if (line->current_line < 0)
	// 	line->current_line = 0;
}