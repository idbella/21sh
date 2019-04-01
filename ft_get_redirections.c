/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 08:37:04 by sid-bell          #+#    #+#             */
/*   Updated: 2019/04/01 02:16:59 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int     ft_get_redirections(char **commands, t_command *command, int i)
{
    if (!ft_is_redirection(commands[i]))
        return (i);
    if (!ft_isvalidred(commands[i]))
        return (-1);
    if (ft_strequ(commands[i], ">") || ft_strequ(commands[i], ">>"))
    {
        if (!commands[i + 1] || ft_is_token(commands[i + 1]))
            return (-1);
    }
    if (ft_is_aggregation(commands[i]))
    {
        if (command)
            ft_addaggr(command, commands[i]);
    }
    else if (ft_is_redirection(commands[i]) && commands[i + 1] && !ft_is_token(commands[i + 1]))
    {
        if (command)
        {
            if (commands[i][0] == '&')
            {
                commands[i][0] = '1';
                ft_addfile(command, commands, i);
                ft_addaggr(command, "2>&1");
            }
            else
                ft_addfile(command, commands, i);
        }
        else
        {
            if (open(commands[i + 1], ft_is_redirection(commands[i]) == 2 ? APPEND : TRUNC, 0777) < 0)
                ft_printf_fd(2, "21sh: permission denied: %s\n", commands[i + 1]);
        }
        i += 1;
    }
    else
        return(-1);
    return (i);
}