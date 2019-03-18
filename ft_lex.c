/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 22:15:11 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/18 08:23:56 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_addfile(t_command *command, char **commands, int i)
{
	t_outfile	*outfile;
	t_list		*list;

	outfile = (t_outfile *)malloc(sizeof(t_outfile));
	outfile->name = ft_strdup(commands[i + 1]);
	outfile->fd_src = ft_get_fd_src(commands[i]);
	outfile->open_mode = ft_is_redirection(commands[i]) == 2 ? O_APPEND|O_CREAT|O_WRONLY : O_CREAT|O_WRONLY|O_TRUNC;
	list = ft_lstnew(NULL, 0);
	list->content = outfile;
	ft_lstadd(&command->outlist, list);
}

void	ft_addaggr(t_command *command, char *cmd)
{
	t_outfile	*outfile;
	t_list		*list;

	outfile = (t_outfile *)malloc(sizeof(t_outfile));
	outfile->fd_src = ft_get_fd_src(cmd);
	outfile->fd_dest = ft_get_fd_dest(cmd);
	outfile->name = NULL;
	if (outfile->fd_dest == -1)
		outfile->name = ft_strdup("/dev/null");
	list = ft_lstnew(NULL, 0);
	list->content = outfile;
	ft_lstadd(&command->outlist, list);
}

int		ft_lex(char *str, t_list **lst)
{
	char		**commands;
	int 		i;
	t_list		*list;
	t_command	*command;

	str = ft_remove_wsapces(str);
	commands = ft_strsplit(str, -1);
	i = 0;
	command = NULL;
	while (commands[i])
	{
		if (ft_is_token(commands[i]))
		{
			while (commands[i] && ft_strcmp(commands[i], "|"))
			{
				if (!ft_isvalidred(commands[i]))
					return (0);
				if (ft_strequ(commands[i], ">") || ft_strequ(commands[i], ">>"))
				{
					if (!commands[i + 1] || ft_is_token(commands[i + 1]))
						return (0);
				}
				if (ft_is_redirection(commands[i]) && commands[i + 1] && !ft_is_token(commands[i + 1]))
				{
					if (command)
					{
						if (commands[i][0] == '&')
						{
							commands[i][0] = '1';
							ft_addfile(command, commands, i);
							ft_addaggr(command, "2>&1");
						}
						else
							ft_addfile(command, commands, i);
					}
					else
						open(commands[i + 1], ft_is_redirection(commands[i]) == 2 ? O_APPEND|O_CREAT|O_WRONLY : O_CREAT|O_WRONLY|O_TRUNC, 0777);

					i += 2;
					while (commands[i] && !ft_is_token(commands[i]))
						i++;
					i--;
				}
				if (ft_is_aggregation(commands[i]))
				{
					if (command)
					{
						ft_addaggr(command, commands[i]);
					}
				}
				i++;
			}
			if (!commands[i] || ft_strcmp(commands[i], "|"))
				i--;
			else if (ft_strequ(commands[i], "|") && !commands[i + 1])
				return (0);
		}
		else
		{
			command = (t_command *)malloc(sizeof(t_command));
			list = ft_lstnew(NULL, 0);
			command->outlist = NULL;
			if (!(command->argv = ft_get_args(command, commands, &i)))
				return (0);
			list->content = command;
			ft_lstadd(lst, list);
		}
		i++;
	}
	*lst = ft_lstrev(*lst);
	return (1);
}
