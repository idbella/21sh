/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 19:32:49 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/04 19:33:04 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_init(t_params *params, char **env, char **argv, char **text)
{
	*text = NULL;
	argv = NULL;
	params->savedfd[0] = dup(0);
	params->savedfd[1] = dup(1);
	params->savedfd[2] = dup(2);
	params->heredoc = 0;
	params->history = NULL;
	params->env = NULL;
	params->commands = NULL;
	ft_parse_env(env, params);
	params->pwd = ft_pwd();
	params->history_pos = -1;
	signal(SIGINT, ft_sig_int_handler);
}
