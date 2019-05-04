/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 04:30:14 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/04 19:42:11 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

void	ft_reset(t_params *params)
{
	dup2(params->savedfd[0], 0);
	dup2(params->savedfd[1], 1);
	dup2(params->savedfd[2], 2);
	close(params->currentfd[0]);
	close(params->currentfd[1]);
	close(params->currentfd[2]);
}

static void	ft_setup(t_params *params)
{
	params->currentfd[0] = dup(0);
	params->currentfd[1] = dup(1);
	params->currentfd[2] = dup(2);
	params->pid = 0;
}

void	ft_pipe(t_params *params)
{
	pipe(params->pipefd);
	params->currentfd[1] = params->pipefd[1];
	params->currentfd[0] = params->pipefd[0];
}

void	ft_init_exec(t_params *params)
{
	ft_setup(params);
	ft_exec(params, params->commands);
	ft_reset(params);
}

int	ft_is_fd_redirected(t_list *list, int fd1, int fd2)
{
	t_outfile	*out;

	while (list)
	{
		out = (t_outfile *)list->content;
		if (out->name && (out->fd_src == fd1 || out->fd_src == fd2))
			return (1);
		if (!out->name && out->fd_src == 1 && out->fd_dest != 1)
			return (1);
		list = list->next;
	}
	return (0);
}

static int	ft_stderr(t_list *list, t_params *params)
{
	t_outfile	*outfile;
	int			ok;

	ok = 0;
	while (list)
	{
		outfile = (t_outfile *)list->content;
		if (!outfile->name)
		{
			if (outfile->fd_src == 2 && outfile->fd_dest == 1)
			{
				dup2(params->currentfd[1], params->currentfd[2]);
				ok = 1;
			}
		}
		list = list->next;
	}
	return (ok);
}

void	ft_exec(t_params *params, t_list *commands)
{
	t_command	*cmd;
	int			flag;
	int			fd;
	int			red;
	t_list		*pids;

	flag = 0;
	pids = NULL;
	red = 0;
	while (commands)
	{
		params->err = 0;
		flag += flag ? 1 : 0;
		cmd = (t_command *)commands->content;
		dup2(params->currentfd[0], 0);
		close(params->currentfd[0]);
		if (cmd->outlist)
		{
			if ((fd = ft_get_io_red(cmd, params)) || params->currentfd[1] == -1
				|| params->currentfd[2] == -1 || params->currentfd[0] == -1)
			{
				if (fd)
					ft_printf_fd(params->savedfd[2],
						"21sh: %d: Bad file descriptor\n", fd);
				commands = commands->next;
				fd = open("/dev/null", O_RDONLY);
				dup2(fd, 0);
				continue ;
			}
		}
		if (commands->next || cmd->heredoc)
		{
			if (!cmd->heredoc && ft_is_fd_redirected(cmd->outlist, 1, 1))
				flag = flag ? 2 : 1;
			else
				ft_pipe(params);
		}
		else
		{
			if (!ft_is_fd_redirected(cmd->outlist, 1, 1))
			{
				close(params->currentfd[1]);
				params->currentfd[1] = dup(params->savedfd[1]);
			}
			if (!ft_is_fd_redirected(cmd->outlist, 2, 2))
			{
				close(params->currentfd[2]);
				params->currentfd[2] = dup(params->savedfd[2]);
			}
		}
		params->err = ft_stderr(cmd->outlist, params);
		dup2(params->currentfd[1], 1);
		dup2(params->currentfd[2], 2);
		close(params->currentfd[1]);
		if (params->err)
			close(params->currentfd[2]);
		if (ft_isbuilt_in(cmd->argv[0]) || cmd->heredoc)
		{
			if (cmd->heredoc)
			{
				ft_printf_fd(1, "%s", cmd->heredoc);
				cmd->heredoc = NULL;
				continue ;
			}
			ft_built_in(cmd, params);
		}
		else
		{
			if (flag >= 2)
			{
				if (!ft_is_fd_redirected(cmd->outlist, 0, 0))
				{
					fd = open("/dev/null", O_RDONLY);
					dup2(fd, 0);
					close(fd);
				}
				flag = 0;
			}
			if (ft_run(params, cmd))
			{
				ft_lstadd(&pids, ft_lstnew(cmd->argv[0],
					ft_strlen(cmd->argv[0]) + 1));
				pids->content_size = params->pid;
			}
		}
		commands = commands->next;
	}
	if (params->pid)
	{
		params->waiting = 1;
		waitpid(params->pid, NULL, 0);
		params->waiting = 0;
	}
	while (pids)
	{
		if (pids->content_size > 0)
			kill(pids->content_size, SIGKILL);
		pids = pids->next;
	}
}
