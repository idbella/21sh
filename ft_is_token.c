/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 19:08:51 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/12 19:09:11 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int ft_is_token(char *str)
{
	int		i;
	int		qoute[2];

	i = 0;
	qoute[0] = 0;
	qoute[1] = 0;
	while (str[i])
	{
		ft_qoutes(str[i], qoute);
		if (!qoute[0] && !qoute[1] && ft_is_special_key(str[i]) && str[i] != '&')
			return (1);
		i++;
	}
	return (0);
}
