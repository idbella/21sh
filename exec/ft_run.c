/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:05:59 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/04 21:19:20 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

int		ft_run(t_params *params, t_command *cmd)
{
	char	*file;
	char	**env;
	t_stat	state;


	if ((file = ft_find_file(cmd->argv[0], params->env))
		&& lstat(file, &state) == 0)
	{
		if ((S_ISREG(state.st_mode) || S_ISLNK(state.st_mode))
			&& !access(file, X_OK))
		{
			env = ft_get_env(params->env);
			params->pid = fork();
			if (!params->pid)
			{
				close(params->currentfd[1]);
				execve(file, cmd->argv, env);
				ft_printf_fd(2, "");
				exit(1);
			}
		}
		else
		{
			ft_printf_fd(2, "21sh: permission denied: %s\n", cmd->argv[0]);
			return (0);
		}
	}
	else
	{
		ft_printf_fd(2, "%s %s\n", "21sh: command not found:", cmd->argv[0]);
		return (0);
	}
	ft_free_tab(env);
	return (1);
}
