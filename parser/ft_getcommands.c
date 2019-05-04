/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcommands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 18:53:19 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/04 19:31:53 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

char	**ft_getcommands(char *str)
{
	char *tmp;
	char **commands;

	tmp = str;
	str = ft_remove_wsapces(str);
	free(tmp);
	commands = ft_strsplit(str, DELEMITER);
	return (commands);
}
