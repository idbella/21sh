/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 00:33:37 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/12 22:49:05 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

void	ft_built_in(t_command *cmd, t_params *params)
{
	// if (!ft_strcmp(name, "cd"))
	// 	ft_cd(cmd->argv[1], params);
	char *name = cmd->argv[0];
	if (!ft_strcmp(name, "echo"))
		ft_echo(cmd);
	if (!ft_strcmp(name, "env"))
		ft_env(params->env);
	if (!ft_strcmp(name, "setenv"))
		ft_setenv(cmd->argv[1], cmd->argv[2], params);
	if (!ft_strcmp(name, "unsetenv"))
		ft_unsetenv(cmd->argv[1], params);
	else if (!ft_strcmp(name, "exit"))
		exit(0);
	// else if (!ft_strcmp(name, "history"))
	// 	ft_history(params->history);
	// else if (!ft_strcmp(name, "set_preview"))
	// 	params->preview_mode = 1;
	// else if (!ft_strcmp(name, "unset_preview"))
	// 	params->preview_mode = 0;
}
