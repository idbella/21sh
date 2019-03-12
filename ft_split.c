/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 21:44:26 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/12 21:44:41 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_split(char *str, t_params *params)
{
	int		i;
	int		start;
	int		qoute[2];
	char	*cmd;

	i = -1;
	qoute[0] = 0;
	qoute[1] = 0;
	start = 0;
	while (str[++i])
	{
		if (!qoute[0] && !qoute[1] && str[i] == ';')
		{
			cmd = ft_strsub(str, start, i - start);
			ft_parse(cmd, params);
			start = i + 1;
		}
		ft_qoutes(str[i], &qoute[0]);
		if (!str[i + 1] && str[i] != ';')
		{
			cmd = ft_strsub(str, start, i - start + 1);
			ft_parse(cmd, params);
		}
	}
	params->commands = ft_lstrev(params->commands);
}
