/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 10:50:43 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/04 18:25:26 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"
#include "../term_cap/line_edit.h"

static void	ft_helper(char **doc, char *line)
{
	char *tmp;

	tmp = *doc;
	*doc = ft_strjoin(*doc, line);
	free(tmp);
	tmp = *doc;
	*doc = ft_strjoin(*doc, "\n");
	free(tmp);
}

char		*ft_here_doc(char *eof, t_params *params)
{
	char	*line;
	char	*doc;

	doc = ft_strnew(0);
	params->heredoc = 1;
	while (1)
	{
		line = read_setup(params);
		if (params->ctrlc)
		{
			params->newcmd = line;
			free(doc);
			return (NULL);
		}
		if (ft_strequ(eof, line) || !line)
		{
			free(line);
			break ;
		}
		ft_helper(&doc, line);
	}
	params->heredoc = 0;
	return (doc);
}
