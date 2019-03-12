/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 04:30:14 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/13 00:01:47 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	ft_setup(t_params *params)
{
	params->savedfd[0] = dup(0);
	params->savedfd[1] = dup(1);
	if (params->infile)
		params->currentfd[0] = open(params->infile, O_RDONLY);
	else
		params->currentfd[0] = dup(params->savedfd[0]);
}

static void ft_getoufile(t_command *cmd, t_params *params)
{
	char		*file;
	t_outfile	*outfile;

	cmd->outlist = ft_lstrev(cmd->outlist);
	while (cmd->outlist)
	{
		outfile = (t_outfile *)cmd->outlist->content;
		file = outfile->name;
		if ((params->currentfd[1] = open(file, outfile->open_mode, 0777)) < 0)
		{
			ft_putendl("Permission Denied");
			break ;
		}
		if (cmd->outlist->next)
			close(params->currentfd[1]);
		cmd->outlist = cmd->outlist->next;
	}
}

int		ft_run(t_params *params, t_command *cmd)
{
	char	*file;

g_params = params;
	if ((file = ft_find_file(cmd->argv[0], params->env)))
	{
		params->pid = fork();
		if (!params->pid)
		{
			execv(file, cmd->argv);
			ft_putendl(cmd->argv[0]);
			ft_putendl("Unknown error");
			exit(1);
		}
		else
		{
			return (1);
		}
	}
	else
	{
		ft_putstr_fd("21sh: command not found: ", params->savedfd[1]);
		ft_putendl_fd(cmd->argv[0], params->savedfd[1]);
		return (0);
	}
}

void	ft_reset(t_params *params)
{
	params->commands = NULL;
	params->infile = NULL;
	dup2(params->savedfd[0], 0);
	dup2(params->savedfd[1], 1);
	close(params->savedfd[0]);
	close(params->savedfd[1]);
}

void	ft_pipe(t_params *params)
{
	pipe(params->pipefd);
	params->currentfd[1] = params->pipefd[1];
	params->currentfd[0] = params->pipefd[0];
}

void    ft_init_exec(t_params *params)
{
    t_list *commands;

    commands = params->commands;
    while (commands)
    {
        ft_setup(params);
        t_list *lst = commands->content;
        ft_exec(params, lst);
        ft_reset(params);
        commands = commands->next;
    }
}

void	ft_exec(t_params *params, t_list *commands)
{
	t_command	*cmd;

	while (commands)
	{
		cmd = (t_command *)commands->content;
		
		dup2(params->currentfd[0], 0);
		close(params->currentfd[0]);
		if (cmd->outlist)
		{
			ft_getoufile(cmd, params);
			if (params->currentfd[1] == -1)
			{
				commands = commands->next;
				continue ;
			}
		}
		else if (!commands->next)
			params->currentfd[1] = dup(params->savedfd[1]);
		else
			ft_pipe(params);
		dup2(params->currentfd[1], 1);
		close(params->currentfd[1]);
		if (ft_isbuilt_in(cmd->argv[0]))
			ft_built_in(cmd, params);
		else
		{
			if (!ft_run(params, cmd))
				break ;
		}
		
		commands = commands->next;
	}
	ft_putendl_fd("<<<<", params->savedfd[1]);
		waitpid(params->pid, NULL,0);
	ft_putendl_fd(">>>>", params->savedfd[1]);
}
