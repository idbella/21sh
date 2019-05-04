/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 21:47:21 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/04 19:31:26 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

void		ft_helper(int *i2, int i, char *line)
{
	while (*i2)
	{
		if (ft_isspace(line[*i2]))
			break ;
		if (!ft_isdigit(line[*i2]))
		{
			if (line[i] == '>' && line[*i2] == '&')
			{
				if (*i2 > 0 && line[*i2 - 1] == '>')
				{
					*i2 = i;
					break ;
				}
				if (*i2 == i - 1)
					break ;
				(*i2)++;
				break ;
			}
			(*i2) = i;
			break ;
		}
		(*i2)--;
	}
}

int			ft_func1(int i, char *line)
{
	int i2;

	i2 = i;
	if (line[i] == '>' || line[i] == '<')
	{
		i2 = i - 1;
		ft_helper(&i2, i, line);
	}
	return (i2);
}

int			ft_func2(int i, int i2, char **line)
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

static int	ft_parse_error(t_params *params)
{
	ft_free_cmd_list(params->commands);
	if (!params->ctrlc)
		ft_putendl("21sh: syntax error.");
	params->commands = NULL;
	return (1);
}

void		ft_parse(char *line, t_params *params)
{
	int		i;
	int		i2;
	char	qoute[2];

	i = -1;
	ft_bzero(qoute, 2);
	i2 = 0;
	while (line[++i])
	{
		if (!qoute[0] && !qoute[1] &&
			ft_is_special_key(line[i]) && line[i] != '&')
		{
			i2 = ft_func1(i, line);
			if ((i = ft_func2(i, i2, &line)) < 0 && ft_parse_error(params))
				return ;
		}
		ft_qoutes(line[i], qoute);
	}
	if (!ft_lex(line, params) && ft_parse_error(params))
		return ;
	params->commands = ft_lstrev(params->commands);
	ft_init_exec(params);
	ft_free_cmd_list(params->commands);
	params->commands = NULL;
}
