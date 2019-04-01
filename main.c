/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:46:13 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/31 03:28:18 by sid-bell         ###   ########.fr       */
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

static char     ft_isqoute(char *str)
{
	int     index;
	int qoutes;
	int     dqouts;

	index = 0;
	qoutes = 0;
	dqouts = 0;
	while (str[index])
	{
			if (!(qoutes % 2) && str[index] == '\"')
					dqouts++;
			else if (!(dqouts % 2) && str[index] == '\'')
					qoutes++;
			index++;
	}
	if (dqouts % 2)
			return ('\"');
	if (qoutes % 2)
			return ('\'');
	return (0);
}

int main(int argc, char **argv, char **env)
{
	char		*line;
	t_params	params;
	char		*text;
	char		*prefix;
	char		qoute;
	char		*data;

	argc = 0;
	argv = NULL;
	params.env = NULL;
	params.commands = NULL;
	ft_parse_env(env, &params);
	text = NULL;
	prefix = NAME;
	data = NULL;
	while ((line = ft_getline(NULL, prefix)))
	{
		if (text)
		{
			text = ft_strjoin(text, "\n");
			text = ft_strjoin(text, line);
		}
		else
			text = ft_strdup(line);
		if ((qoute = ft_isqoute(text)))
		{
			prefix = qoute == '\'' ? "qoute> " : "dqoute> ";
			continue ;
		}
		prefix = NAME;
		ft_handle_qoutes(&text);
		ft_split(text, &params);
		ft_init_exec(&params);
		text = NULL;
		data = NULL;
		params.commands = NULL;
	}
}
/* delete strerror from libft */