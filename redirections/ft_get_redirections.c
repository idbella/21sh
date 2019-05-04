/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 08:37:04 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/04 17:30:08 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

static int	ft_handle_heredoc(t_params *params, t_command *command,
								char **commands, int i)
{
	char	*heredoc;

	if (!commands[i + 1] || ft_is_token(commands[i + 1]))
		return (0);
	commands[i + 1] = ft_remove_qoutes(commands[i + 1]);
	ft_unescape(commands[i + 1]);
	if ((heredoc = ft_here_doc(commands[i + 1], params)))
	{
		command->heredoc = heredoc;
		return (i + 1);
	}
	return (-1);
}

static void	ft_aggr(char **commands, t_command *command, int i)
{
	if (commands[i][0] == '&')
	{
		commands[i][0] = '1';
		ft_addfile(command, commands, i);
		ft_addaggr(command, "2>&1", NULL);
	}
	else
		ft_addfile(command, commands, i);
}

static void	ft_handle_red(t_command *command,
							char **commands, int i)
{
	int		type;

	if (command)
		ft_aggr(commands, command, i);
	else
	{
		type = ft_is_redirection(commands[i]);
		if (type == 3)
			type = O_RDONLY;
		else
			type = type == 2 ? APPEND : TRUNC;
		if (type != O_RDONLY || ft_exist(commands[i + 1]))
		{
			if (open(commands[i + 1], type, 0777) < 0)
				ft_printf_fd(2, "21sh: permission denied: %s\n",
					commands[i + 1]);
		}
		else
			ft_printf_fd(1, "21sh: no such file or directory: %s\n",
						commands[i + 1]);
	}
}

static int	ft_handle_aggr(char **commands, t_command *command, int *i)
{
	int res;

	if ((res = ft_is_aggregation(commands[*i], commands[*i + 1])))
	{
		if (res == -1)
			return (-1);
		if (command)
			ft_addaggr(command, commands[*i],
				res == 2 ? commands[*i + 1] : NULL);
		if (res == 2)
			(*i)++;
	}
	else
		return (0);
	return (*i);
}

int			ft_get_redirections(char **commands, t_command *command,
							int i, t_params *params)
{
	int ret;

	if (!ft_is_redirection(commands[i]))
		return (i);
	if (!ft_isvalidred(commands[i]) || !ft_check(commands, i))
		return (-1);
	if (ft_strequ(commands[i], "<<"))
		return (ft_handle_heredoc(params, command, commands, i));
	if ((ret = ft_handle_aggr(commands, command, &i)))
		return (ret);
	else if (ft_is_redirection(commands[i]) && commands[i + 1]
			&& !ft_is_token(commands[i + 1]))
	{
		ft_handle_red(command, commands, i);
		i += 1;
	}
	else
		return (-1);
	return (i);
}
