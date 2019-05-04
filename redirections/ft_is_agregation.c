/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_agregation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 22:10:58 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/02 23:52:46 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

int		ft_is_aggregation(char *current, char *next)
{
	int len;

	if (ft_strstr(current, ">&") || ft_strstr(current, "<&"))
	{
		len = ft_strlen(current);
		if (current[len - 1] == '-' || ft_isdigit(current[len - 1]))
			return (1);
		else
		{
			if (!next)
				return (-1);
			while (*next)
			{
				if (!ft_isdigit(*next))
					return (0);
				next++;
			}
			return (2);
		}
	}
	return (0);
}
