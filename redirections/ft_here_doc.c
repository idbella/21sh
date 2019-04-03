/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 10:50:43 by sid-bell          #+#    #+#             */
/*   Updated: 2019/04/03 12:13:08 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

char    *ft_here_doc(char *eof, t_params *params)
{
	char	*line;
	char	*doc;
	char	*tmp;

	doc = ft_strnew(0);
	while(1)
	{
		line = ft_getline(NULL, "heredoc> ", params);
		tmp = doc;
		doc = ft_strjoin(doc, line);
		free(tmp);
		if (ft_strequ(eof, line))
			break ;
		doc = ft_strjoin(doc, "\n");
	}
	return (doc);
}