/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 00:33:37 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/03 21:26:55 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_echo(t_command *cmd)
{
	int		i;
	char	**args;

	i = 1;
	args = cmd->argv;
	while (args[i])
	{
		ft_putstr(args[i]);
		i++;
		if (args[i])
			ft_putchar(' ');
	}
	ft_putchar('\n');
}
