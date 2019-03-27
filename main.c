/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:46:13 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/26 23:52:52 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	ft_setup(t_line *line)
{
	char	*term;
	char	buff[2048];
	struct	termios termio;

	term = getenv("TERM");	
	tgetent(buff, term);	
	tcgetattr(0, &termio);
	termio.c_lflag = ~ICANON & termio.c_lflag;
	termio.c_lflag = ~ECHO & termio.c_lflag;
	tcsetattr(0, TCSANOW, &termio);
	line->delete = tgetstr("dl", NULL);
	line->mv_up = tgetstr("up", NULL);
	line->mv_left = tgetstr("le", NULL);
 	line->mv_down = tgetstr("do", NULL);
	line->mv_right = tgetstr("nd", NULL);
	line->reverse_v = tgetstr("mr", NULL);
	line->stop_v = tgetstr("me", NULL);
	line->prefix = NAME;
}

int main(int argc, char **argv, char **env)
{
	char		*line;
	t_params	params;
	t_line		line_params;

	argc = 0;
	argv = NULL;
	params.env = NULL;
	params.commands = NULL;
	ft_parse_env(env, &params);
	ft_setup(&line_params);
	while ((line = ft_getline(&line_params)))
	{
		ft_handle_qoutes(&line);
		ft_split(line, &params);
		ft_init_exec(&params);
		params.commands = NULL;
	}
}
