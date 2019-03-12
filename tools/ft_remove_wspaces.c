/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_wspaces.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 00:33:37 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/12 22:51:01 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

static void	ft_helper(char *c, int *qoute, int *dqoute)
{
	if (!*dqoute && !*qoute && ft_isspace(*c))
		*c = -1;
	else if (!*qoute && *c == '\"')
	{
		//*c = DQOUTE;
		*dqoute = !*dqoute;
	}
	else if (!*dqoute && *c == '\'')
	{
		//*c = QOUTE;
		*qoute = !*qoute;
	}
}

char		*ft_remove_wsapces(char *str)
{
	int		qoute;
	int		dqoute;
	int		i;
	char	*result;

	result = ft_strdup(str);
	qoute = 0;
	dqoute = 0;
	str = result;
	result = ft_strtrim(result);
	free(str);
	i = 0;
	while (result[i])
	{
		ft_helper(&result[i], &qoute, &dqoute);
		i++;
	}
	return (result);
}
