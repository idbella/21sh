/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 19:34:10 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/04 19:34:20 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term_cap/line_edit.h"

int		check_syntax(char *syntax, char c)
{
	if (!syntax)
		return (1);
	if (!*syntax && c == 0)
		return (1);
	else if (!*syntax && c != 0)
		return (-2);
	else if (c == 0 && *syntax == '\\' && !*(syntax + 1))
		return (-1);
	if (*syntax == c)
		return (check_syntax(++syntax, 0));
	if (*syntax == '\\' && (c == 0 || c == '"') &&
		(*(syntax + 1) == '"' || *(syntax + 1) == '\'' || *(syntax + 1)
			== '\\'))
		return (check_syntax(syntax + 2, c));
	if (*syntax == '"' && c == 0)
		return (check_syntax(++syntax, '"'));
	else if (*syntax != '"' && c == '"')
		return (check_syntax(++syntax, '"'));
	if (*syntax == '\'' && c == 0)
		return (check_syntax(++syntax, '\''));
	else if (*syntax != '\'' && c == '\'')
		return (check_syntax(++syntax, '\''));
	return (check_syntax(++syntax, c));
}

char	*read_line(t_params *params)
{
	int		ret;
	char	*buffer;
	char	*tmp;
	int		i;

	tmp = read_setup(params);
	if (tmp)
		while ((ret = check_syntax(tmp, 0)) < 0)
		{
			params->quate = 1;
			ft_putendl("~>>");
			buffer = read_setup(params);
			if (params->ctrlc)
			{
				tmp = buffer;
				params->ctrlc = 0;
				continue;
			}
			i = 0;
			if (ret == -1 && buffer)
				while (buffer[i])
					tmp = joinchar(&tmp, buffer[i++], 0, 0);
			else if (buffer)
			{
				tmp = joinchar(&tmp, '\n', 0, 0);
				while (buffer[i])
					tmp = joinchar(&tmp, buffer[i++], 0, 0);
			}
			free(buffer);
		}
	(tmp) ? addtohistory(params, tmp) : 0;
	params->quate = 0;
	return (tmp);
}
