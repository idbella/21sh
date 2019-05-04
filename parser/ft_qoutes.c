/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qoutes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 20:31:00 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/03 20:46:38 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

int			ft_is_qoute(char c)
{
	return (c == '\"' || c == '\'');
}

char		*ft_join_qoutes(char *line)
{
	char	*str;
	char	*tmp;
	int		i;
	char	qoute[2];

	ft_bzero(qoute, 2);
	i = -1;
	while (line[++i])
	{
		ft_qoutes(line[i], qoute);
		if (!(qoute[0] || qoute[1]))
		{
			if (ft_is_qoute(line[i]) && line[i] == line[i + 1])
			{
				str = ft_strsub(line, 0, i);
				tmp = line;
				line = ft_strjoin(str, line + i + 2);
				free(tmp);
			}
			else if (ft_is_qoute(line[i]) && ft_is_qoute(line[i + 1]))
				line = ft_insertchar(&line, -2, i + 1);
		}
	}
	return (line);
}

void		ft_qoutes(char c, char *qoute)
{
	if (!qoute[1] && c == '\'')
		qoute[0] = !qoute[0];
	else if (!qoute[0] && c == '\"')
		qoute[1] = !qoute[1];
}

void		ft_handle_qoutes(char **line, t_params *params)
{
	*line = ft_gethome(*line, params);
	*line = ft_getvars(*line, params);
	*line = ft_joinargs(*line);
	ft_strrev(*line);
	*line = ft_joinargs(*line);
	ft_strrev(*line);
	*line = ft_join_qoutes(*line);
}
