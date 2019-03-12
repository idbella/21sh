/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:46:13 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/11 00:05:50 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int main(int argc, char **argv)
{
	char		*line;
	t_params	params;

	params.commands = NULL;
	ft_putstr("$> ");
	while (get_next_line(0, &line) > 0)
	{
		ft_handle_qoutes(line, &params);
		ft_putstr("$> ");
	}
}
