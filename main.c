/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:46:13 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/14 21:41:25 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_print(t_list *list)
{
	t_command	*cmd;
	t_list  	*lst;
	t_outfile	*out;

	while (list)
	{
		cmd = (t_command *)list->content;
		printf("\n\n\n\nname = %s\n", cmd->argv[0]);
		lst = cmd->outlist;
		while (lst)
		{
			out = (t_outfile *)lst->content;
			if (out->name)
				printf("redirect fd %d to %s\n", out->fd_src, out->name);
			else
			{
				printf("\tredirect fd %d to fd %d\n", out->fd_src, out->fd_dest);
			}
			lst = lst->next;
		}
		list = list->next;
	}
}

int main(int argc, char **argv, char **env)
{
	char		*line;
	t_params	params;

	argc = 0;
	argv = NULL;
	params.env = NULL;
	params.commands = NULL;
	params.infile = NULL;
	ft_parse_env(env, &params);
	ft_putstr("$> ");
	while (get_next_line(0, &line) > 0)
	{
		ft_handle_qoutes(&line);
		ft_split(line, &params);
		ft_init_exec(&params);
		//ft_print((t_list *)params.commands->content);
		ft_putstr("$> ");
		params.commands = NULL;
	}
}
