/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinargs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 00:33:37 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/03 20:44:52 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

int			ft_is_special_key(char c)
{
	return (c == '|' || c == '>' || c == '<' || c == '&');
}

static int	ft_helper1(char *str, int r)
{
	while (r >= 0)
	{
		if (ft_is_qoute(str[r]) || ft_isspace(str[r])
			|| ft_is_special_key(str[r]))
			break ;
		r--;
	}
	return (r);
}

static void	ft_helper(char *qoute, char c)
{
	qoute[0] = c == '\'' ? 1 : 0;
	qoute[1] = c == '\"' ? 1 : 0;
}

char		*ft_joinargs(char *str)
{
	int		i[2];
	char	qoute[2];
	char	c;
	char	*result;

	ft_bzero(qoute, 2);
	i[0] = -1;
	result = ft_strdup(str);
	free(str);
	while (result[++i[0]])
	{
		ft_qoutes(result[i[0]], qoute);
		if (!qoute[0] && !qoute[1] && !ft_isspace(result[i[0]])
			&& ft_is_qoute(result[i[0] + 1]) &&
			!ft_is_special_key(result[i[0]]) && result[i[0]] != ';')
		{
			i[1] = ft_helper1(result, i[0]);
			c = result[i[0] + 1];
			result = ft_delchar(result, i[0] + 1);
			result = ft_insertchar(&result, c, i[1] + 1);
			ft_helper(qoute, c);
			i[0]++;
		}
	}
	return (result);
}
