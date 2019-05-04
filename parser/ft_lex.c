/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 22:15:11 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/04 21:16:48 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

void	ft_addfile(t_command *command, char **commands, int i)
{
	t_outfile	*outfile;
	t_list		*list;
	int			type;

	outfile = (t_outfile *)malloc(sizeof(t_outfile));
	outfile->name = ft_remove_qoutes(ft_strdup(commands[i + 1]));
	ft_unescape(outfile->name);
	outfile->fd_src = ft_get_fd_src(commands[i]);
	outfile->close = 0;
	type = ft_is_redirection(commands[i]);
	if (type == 3)
		outfile->open_mode = O_RDONLY;
	else
		outfile->open_mode = type == 2 ? APPEND : TRUNC;
	list = ft_lstnew(NULL, 0);
	list->content = outfile;
	ft_lstadd(&command->outlist, list);
}

void	ft_addaggr(t_command *command, char *cmd, char *next)
{
	t_outfile	*outfile;
	t_list		*list;

	outfile = (t_outfile *)malloc(sizeof(t_outfile));
	outfile->fd_src = ft_get_fd_src(cmd);
	outfile->fd_dest = ft_get_fd_dest(next ? next : cmd);
	outfile->name = NULL;
	outfile->close = 0;
	if (outfile->fd_dest == -1)
		outfile->name = ft_strdup("/dev/null");
	list = ft_lstnew(NULL, 0);
	list->content = outfile;
	ft_lstadd(&command->outlist, list);
}

int		ft_ontimecheck(t_params *params,
			t_command *command, char **commands, int *i)
{
	if (ft_is_token(commands[*i]))
	{
		if (ft_strequ(commands[*i], "|")
			&& (!commands[*i + 1] || command == NULL))
		{
			ft_free_tab(commands);
			return (-1);
		}
		else if ((*i = ft_get_redirections(commands,
								command, *i, params)) < 0)
		{
			ft_free_tab(commands);
			return (-1);
		}
		return (1);
	}
	return (0);
}

int		ft_lex(char *str, t_params *params)
{
	char		**commands;
	int			i;
	t_command	*command;
	int			return_value;

	commands = ft_getcommands(str);
	i = -1;
	command = NULL;
	while (commands[++i])
	{
		if ((return_value = ft_ontimecheck(params, command, commands, &i)))
		{
			if (return_value < 0)
				return (0);
		}
		else
		{
			if (!ft_addcmd(command, commands, params, &i))
				return (0);
		}
	}
	return (1);
}
