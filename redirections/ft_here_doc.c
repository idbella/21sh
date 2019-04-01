/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 10:50:43 by sid-bell          #+#    #+#             */
/*   Updated: 2019/04/01 22:13:38 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

char    *ft_here_doc(char *eof)
{
	char	*line;
	char	*doc;
	char	*tmp;

	doc = ft_strnew(0);
	while(get_next_line(0, &line) > 0)
	{
		tmp = doc;
		doc = ft_strjoin(doc, line);
		free(tmp);
		if (ft_strequ(eof, line))
			break ;
	}
	return (doc);
}