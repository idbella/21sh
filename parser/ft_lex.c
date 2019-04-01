/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 22:15:11 by sid-bell          #+#    #+#             */
/*   Updated: 2019/04/01 22:52:39 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

void	ft_addfile(t_command *command, char **commands, int i)
{
	t_outfile	*outfile;
	t_list		*list;
	int			type;

	outfile = (t_outfile *)malloc(sizeof(t_outfile));
	outfile->name = ft_strdup(commands[i + 1]);
	outfile->fd_src = ft_get_fd_src(commands[i]);
	type = ft_is_redirection(commands[i]);
	if (type == 3)
		outfile->open_mode = O_RDONLY;
	else
		outfile->open_mode = type == 2 ? APPEND : TRUNC;
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
			if (ft_strequ(commands[i], "|") && !commands[i + 1])
				return (0);
			if ((i = ft_get_redirections(commands, command, i)) < 0)
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
