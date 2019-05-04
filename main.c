/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:46:13 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/04 19:35:14 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"
#include "term_cap/line_edit.h"

int		main(int argc, char **argv, char **env)
{
	char		*text;

	argc = 0;
	ft_init(&params, env, argv, &text);
	signal(SIGWINCH, ft_sig_win_handler);
	while (1)
	{
		ft_print_path(&params);
		text = read_line(&params);
		if (text)
		{
			ft_escape(&text);
			ft_handle_qoutes(&text, &params);
			ft_split(text, &params);
			text = NULL;
			params.commands = NULL;
			params.ctrlc = 0;
			if (params.newcmd)
			{
				ft_split(params.newcmd, &params);
				free(params.newcmd);
				params.newcmd = NULL;
			}
		}
	}
}
