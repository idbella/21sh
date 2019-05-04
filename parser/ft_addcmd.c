/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addcmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 18:54:03 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/04 18:54:48 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

int	ft_addcmd(t_command *command, char **commands,
						t_params *params, int *i)
{
	t_list		*list;

	command = (t_command *)malloc(sizeof(t_command));
	command->heredoc = NULL;
	list = ft_lstnew(NULL, 0);
	command->outlist = NULL;
	if (!(command->argv = ft_get_args(command, commands, i, params)))
	{
		ft_free_tab(commands);
		return (0);
	}
	list->content = command;
	ft_lstadd(&params->commands, list);
	return (1);
}
