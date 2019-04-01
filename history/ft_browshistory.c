/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_browshistory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 00:33:37 by sid-bell          #+#    #+#             */
/*   Updated: 2019/04/01 20:45:57 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

static void	ft_helper(t_params *params, t_line *line)
{
	t_list	*list;
	int		pos;

	pos = 0;
	list = params->history;
	while (list)
	{
		if (pos == params->history_pos)
		{
			free(line->data);
			line->data = ft_strdup((char *)list->content);
			line->cursor = 0;
			break ;
		}
		pos++;
		list = list->next;
	}
}

void		ft_browshistory(t_line *line, t_params *params)
{
	int		len;

	if (line->c == C_UP)
	{
		len = ft_lstcount(params->history);
		if (params->history && params->history_pos + 1 < len)
			params->history_pos += 1;
		else
			return ;
	}
	else
	{
		if (params->history_pos < 0)
			return ;
		params->history_pos -= 1;
		if (params->history_pos == -1)
		{
			free(line->data);
			line->data = ft_strnew(0);
			line->cursor = 0;
		}
	}
	if (params->history_pos >= 0)
		ft_helper(params, line);
}
