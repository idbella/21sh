/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 21:44:26 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/04 17:59:30 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

void	ft_split(char *str, t_params *params)
{
	int		i;
	int		start;
	char	qoute[2];
	char	*cmd;

	i = -1;
	ft_bzero(qoute, 2);
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
		if (params->ctrlc)
			return ;
	}
}
