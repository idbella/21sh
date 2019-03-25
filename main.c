/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:46:13 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/25 19:12:23 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// void	ft_print2(t_list *list)
// {
// 	t_command	*cmd;
// 	t_list  	*lst;
// 	t_outfile	*out;

// 	while (list)
// 	{
// 		cmd = (t_command *)list->content;
// 		printf("\n\n\n\nname = %s\n", cmd->argv[0]);
// 		int i = 1;
// 		while(cmd->argv[i])
// 		{
// 			printf("\t%s\n", cmd->argv[i]);
// 			i++;
// 		}
// 		lst = cmd->outlist;
// 		while (lst)
// 		{
// 			out = (t_outfile *)lst->content;
// 			if (out->name)
// 				printf("redirect fd %d to %s\n", out->fd_src, out->name);
// 			else
// 			{
// 				printf("\tredirect fd %d to fd %d\n", out->fd_src, out->fd_dest);
// 			}
// 			lst = lst->next;
// 		}
// 		list = list->next;
// 	}
// }

int main(int argc, char **argv, char **env)
{
	char		*line;
	t_params	params;

	argc = 0;
	argv = NULL;
	params.env = NULL;
	params.commands = NULL;
	ft_parse_env(env, &params);
	while ((line = ft_getline()))
	{
		ft_handle_qoutes(&line);
		ft_split(line, &params);
		ft_init_exec(&params);
		params.commands = NULL;
	}
}
