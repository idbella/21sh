/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 00:33:37 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/02 22:31:32 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

void	ft_exit(t_params *params)
{
	ft_free_cmd_list(params->commands);
	exit(0);
}

void	ft_built_in(t_command *cmd, t_params *params)
{
	char *name;

	name = cmd->argv[0];
	if (!ft_strcmp(name, "cd"))
		ft_cd(cmd->argv[1], params);
	if (!ft_strcmp(name, "echo"))
		ft_echo(cmd);
	if (!ft_strcmp(name, "env"))
		ft_env(params->env);
	if (!ft_strcmp(name, "setenv"))
		ft_setenv(cmd->argv[1], cmd->argv[2], params);
	if (!ft_strcmp(name, "unsetenv"))
		ft_unsetenv(cmd->argv[1], params);
	else if (!ft_strcmp(name, "exit"))
		ft_exit(params);
	else if (!ft_strcmp(name, "history"))
		ft_history(params->history);
}
