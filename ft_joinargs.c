/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinargs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 00:33:37 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/12 05:06:58 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			ft_is_special_key(char c)
{
	return (c == '|' || c == '>' || c == '<' || c == '&');
}

int			ft_is_qoute(char c)
{
	return (c == '\"' || c == '\'');
}

static int	ft_helper1(char *str, int r)
{
	while (r >= 0)
	{
		if (ft_is_qoute(str[r]) || ft_isspace(str[r]) || ft_is_special_key(str[r]))
			break ;
		r--;
	}
	return (r);
}

void	ft_qoutes(char c, int *qoute)
{
	if (c == '\'')
		qoute[0] = !qoute[0];
	else if (c == '\"')
		qoute[1] = !qoute[1];
}

char		*ft_joinargs(char *str)
{
	int		i[2];
	int		qoute[2];
	char	c;
	char	*result;

	qoute[0] = 0;
	qoute[1] = 0;
	i[0] = -1;
	result = ft_strdup(str);
	free(str);
	while (result[++i[0]])
	{
		ft_qoutes(result[i[0]], qoute);
		if (!qoute[0] && !qoute[1] && !ft_isspace(result[i[0]]) &&
			ft_is_qoute(result[i[0] + 1]) && !ft_is_special_key(result[i[0]]))
		{
			i[1] = ft_helper1(result, i[0]);
			c = result[i[0] + 1];
			result = ft_delchar(&result, i[0] + 1);
			result = ft_insertchar(&result, c, i[1] + 1);
			qoute[0] = c == '\'' ? 1 : 0;
			qoute[1] = c == '\"' ? 1 : 0;
			i[0]++;
		}
	}
	return (result);
}

char		*ft_join_qoutes(char *line)
{
	char	*str;
	char	*tmp;
	int		i;
	int		qoute[2];

	qoute[0] = 0;
	qoute[1] = 0;
	i = 0;
	while (line[i])
	{
		if (!qoute[0] && !qoute[1] && ft_is_qoute(line[i]) && line[i] == line[i + 1])
		{
			str = ft_strsub(line, 0, i);
			tmp = line;
			line = ft_strjoin(str, line + i + 2);
			free(tmp);
		}
		ft_qoutes(line[i], qoute);
		i++;
	}
	return (line);
}

void		ft_handle_qoutes(char **line)
{
	*line = ft_joinargs(*line);
	ft_strrev(*line);
	*line = ft_joinargs(*line);
	ft_strrev(*line);
	*line = ft_join_qoutes(*line);
}
