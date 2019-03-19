/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 21:47:21 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/19 15:23:33 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		ft_func1(int i, char *line)
{
	int i2;

	i2 = i;
	if (line[i] == '>' || line[i] == '<')
	{
		i2 = i - 1;
		while (i2)
		{
			if (ft_isspace(line[i2]))
				break ;
			if (!(line[i2] >= '0' && line[i2] <= '9'))
			{
				if (line[i] == '>' && line[i2] == '&')
				{
					if (i2 > 0 && line[i2 - 1] == '>')
					{
						/*  cmd >&1>file*/
						i2 = i;
						break;
					}
					if (i2 == i - 1)
						break ;
					i2++;
					break ;
				}
				i2 = i;
				break;
			}
			i2--;
		}
	}
	return (i2);
}

int		ft_func2(int i, int i2, char **line)
{
	*line = ft_insert_str(*line, " ", i2);
	i++;
	while (ft_is_special_key((*line)[i + 1]))
	{
		i++;
		if ((*line)[i] == '&')
			break ;
	}
	if ((*line)[i + 1] == '&')
		return (-1);
	if (ft_is_special_key((*line)[i]))
	{
		ft_fd_or_file(line, i);
		i++;
	}
	return (i);
}

int		ft_is_redirection(char *str)
{
	if (ft_strstr(str, ">>"))
		return (2);
	if (ft_strstr(str, ">"))
		return (1);
	if (ft_strstr(str, "<"))
		return (3);
	return (0);
}

void ft_parse(char *line, t_params *params)
{
	int		i;
	int		i2;
	int		qoute[2];
	t_list	*commands;
	t_list	*lst;

	i = -1;
	qoute[0] = 0;
	qoute[1] = 0;
	i2 = 0;
	
	while (line[++i])
	{
		if (!qoute[0] && !qoute[1] && ft_is_special_key(line[i]) && line[i] != '&')
		{
			i2 = ft_func1(i, line);
			if ((i = ft_func2(i, i2, &line)) < 0)
			{
				ft_putendl("21sh: syntax error.");
				return ;
			}
		}
		ft_qoutes(line[i], qoute);
	}
	commands = NULL;
	if (!ft_lex(line, &commands))
	{
		ft_putendl("21sh: parse error.");
		return ;
	}
	
	lst = ft_lstnew(NULL, 0);
	lst->content = commands;
	ft_lstadd(&params->commands, lst);
}