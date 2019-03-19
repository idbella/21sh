/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_agregation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 22:10:58 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/19 14:42:19 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		ft_is_aggregation(char *current)
{
	int len;

	if (ft_strstr(current, ">&") || ft_strstr(current, "<&"))
	{
        len = ft_strlen(current);
        if (current[len - 1] == '-' || ft_isdigit(current[len - 1]))
            return (1);		
	}
	return (0);
}
