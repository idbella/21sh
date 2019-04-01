/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:46:13 by sid-bell          #+#    #+#             */
/*   Updated: 2019/04/01 22:30:21 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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

void ft_init(t_params *params, char **env)
{
	params->history = NULL;
	params->env = NULL;
	params->commands = NULL;
	ft_parse_env(env, params);
	params->pwd = ft_pwd();
	params->history_pos = -1;
	ft_load_history(params);
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
	text = NULL;
	prefix = NAME;
	data = NULL;
	ft_init(&params, env);
	while ((line = ft_getline(NULL, prefix, &params)))
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