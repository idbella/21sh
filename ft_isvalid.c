/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isvalid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 22:14:14 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/12 22:19:50 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	ft_isvalidred(char *str)
{
	int count1;
	int count2;
	int count3;

	count1 = 0;
	count3 = 0;
	count2 = 0;
	while (*str)
	{
		if (*str == '>')
			count1++;
		else if (*str == '<')
			count2++;
		else if (*str == '|')
			count3++;
		str++;
	}
	if (((count1 && count2) || (count1 && count3) || (count2 && count3)) || count1 > 2 || count2 > 2 || count3 > 1)
		return (0);
	return (1);
}
