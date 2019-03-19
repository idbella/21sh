/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 04:30:14 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/19 14:30:48 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int ft_getoufile(t_command *cmd, t_params *params)
{
	char		*file;
	t_outfile	*outfile;
	t_list		*list;
	int			src;
	int			dst;

	cmd->outlist = ft_lstrev(cmd->outlist);
	list = cmd->outlist;
	while (list)
	{
		outfile = (t_outfile *)list->content;
		file = outfile->name;
		if (file)
		{
			src = open(file, outfile->open_mode, 0777);
			if ((outfile->fd_src >= 0 && outfile->fd_src <= 2))
			{
				if (outfile->fd_src == 0)
					close(0);
				if (outfile->fd_src == 2 && src > 0)
					dup2(src, params->currentfd[outfile->fd_src]);
				else
					params->currentfd[outfile->fd_src] = src;
			}
			if (src < 0)
			{
				ft_putendl_fd("21sh: Permission Denied:", params->currentfd[2]);
				break ;
			}
		}
		if (!file)
		{
			src = outfile->fd_src;
			dst = outfile->fd_dest;
			if (src < 0 || src > 2)
				return (src);
			if (dst < 0 || dst > 2)
				return (dst);
			if (outfile->fd_src == 1 || outfile->fd_src == 2)
				src = params->currentfd[outfile->fd_src];
			if (outfile->fd_dest == 1 || outfile->fd_dest == 2)
				dst = params->currentfd[outfile->fd_dest];
			dup2(dst, src);
		}
		list = list->next;
	}
	return (0);
}

int		ft_run(t_params *params, t_command *cmd)
{
	char	*file;

	if ((file = ft_find_file(cmd->argv[0], params->env)))
	{
		params->pid = fork();
		if (!params->pid)
		{
			execv(file, cmd->argv);
			ft_putendl(cmd->argv[0]);
			ft_putendl_fd("Unknown error", 2);
			exit(1);
		}
		else
			return (1);
	}
	else
	{
		ft_putstr_fd("21sh: command not found: ", 2);
		ft_putendl_fd(cmd->argv[0], 2);
		return (0);
	}
}

void	ft_reset(t_params *params)
{
	params->infile = NULL;
	dup2(params->savedfd[0], 0);
	dup2(params->savedfd[1], 1);
	dup2(params->savedfd[2], 2);
	close(params->savedfd[0]);
	close(params->savedfd[1]);
	close(params->savedfd[2]);
}

static void	ft_setup(t_params *params)
{
	params->savedfd[0] = dup(0);
	params->savedfd[1] = dup(1);
	params->savedfd[2] = dup(2);
	params->currentfd[1] = dup(1);
	params->currentfd[2] = dup(2);
	params->pid = 0;
	if (params->infile)
		params->currentfd[0] = open(params->infile, O_RDONLY);
	else
		params->currentfd[0] = dup(params->savedfd[0]);
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

int	ft_is_out_redirected(t_list *list, int fd1, int fd2)
{
	t_outfile	*out;

	while(list)
	{
		out = (t_outfile *)list->content;
		if (out->name && (out->fd_src == fd1 || out->fd_src == fd2))
			return (1);
		list = list->next;
	}
	return (0);
}

static int 	ft_stderr(t_list *list, t_params *params)
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

	flag = 0;
	while (commands)
	{
		params->err = 0;
		flag += flag ? 1 : 0; 
		cmd = (t_command *)commands->content;
		dup2(params->currentfd[0], 0);
		close(params->currentfd[0]);
		if (cmd->outlist)
		{
			if ((fd = ft_getoufile(cmd, params)) || params->currentfd[1] == -1 || params->currentfd[2] == -1)
			{
				if (fd)
				{
					ft_putstr_fd("21sh ", params->savedfd[2]);
					ft_putnbr_fd(fd, params->savedfd[2]);
					ft_putendl_fd(": Bad file descriptor", params->savedfd[2]);
				}
				commands = commands->next;
				continue ;
			}
		}
		if (commands->next)
		{
			if (ft_is_out_redirected(cmd->outlist, 1, 1))
				flag = flag ? 2 : 1;
			else
			{
				ft_pipe(params);
				params->err = ft_stderr(cmd->outlist, params);
			}
		}
		else
		{
			if (!ft_is_out_redirected(cmd->outlist, 1, 1))
				params->currentfd[1] = dup(params->savedfd[1]);
			if (!ft_is_out_redirected(cmd->outlist, 2, 2))
				params->currentfd[2] = dup(params->savedfd[2]);
		}
		dup2(params->currentfd[1], 1);
		dup2(params->currentfd[2], 2);
		close(params->currentfd[1]);
		if (params->err)
			close(params->currentfd[2]);
		if (ft_isbuilt_in(cmd->argv[0]))
			ft_built_in(cmd, params);
		else
		{
			if (flag >= 2)
			{
				int fd = open("/dev/null", O_RDONLY);
				dup2(fd, 0);
			}
			if (!ft_run(params, cmd))
				break ;
		}
		commands = commands->next;
	}
	if (params->pid)
		waitpid(params->pid, NULL,0);
}
