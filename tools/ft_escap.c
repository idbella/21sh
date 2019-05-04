/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_escap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 19:00:21 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/04 18:24:55 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

int		ft_getesc(char c)
{
	if (c == 'n')
		return (ESC_NEWLINE);
	else if (c == '\'')
		return (ESC_QOUTE);
	else if (c == '"')
		return (ESC_DQOUTE);
	else if (c == '\\')
		return (ESC_SLASH);
	else if (c == 't')
		return (ESC_TAB);
	else if (c == ' ')
		return (ESC_SPACE);
	return (0);
}

void	ft_escape(char **str)
{
	int i;
	int e;

	i = 0;
	e = 1;
	while (e)
	{
		e = 0;
		i = 0;
		while ((*str)[i])
		{
			if ((*str)[i] == '\\' && (e = ft_getesc((*str)[i + 1])))
			{
				*str = ft_delchar(*str, i);
				(*str)[i] = e;
				break ;
			}
			i++;
		}
	}
}

char	ft_getunesc(char c)
{
	if (c == ESC_NEWLINE)
		return ('\n');
	else if (c == ESC_QOUTE)
		return ('\'');
	else if (c == ESC_DQOUTE)
		return ('"');
	else if (c == ESC_SLASH)
		return ('\\');
	else if (c == ESC_TAB)
		return ('\t');
	else if (c == ESC_SPACE)
		return (' ');
	return (0);
}

void	ft_unescape(char *str)
{
	char c;

	while (*str)
	{
		if ((c = ft_getunesc(*str)))
			*str = c;
		str++;
	}
}
