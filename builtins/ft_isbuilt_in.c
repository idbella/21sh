/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbuilt_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 00:33:37 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/02 22:30:36 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

int		ft_isbuilt_in(char *name)
{
	if (!ft_strcmp(name, "cd"))
		return (1);
	if (!ft_strcmp(name, "echo"))
		return (1);
	if (!ft_strcmp(name, "exit"))
		return (1);
	if (!ft_strcmp(name, "env"))
		return (1);
	if (!ft_strcmp(name, "setenv"))
		return (1);
	if (!ft_strcmp(name, "unsetenv"))
		return (1);
	if (!ft_strcmp(name, "history"))
		return (1);
	if (!ft_strcmp(name, "set_preview"))
		return (1);
	if (!ft_strcmp(name, "unset_preview"))
		return (1);
	return (0);
}
