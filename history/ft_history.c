/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 00:33:37 by sid-bell          #+#    #+#             */
/*   Updated: 2019/04/25 20:42:54 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

void	ft_history(t_list *list)
{
	if (list->next)
		ft_history(list->next);
	ft_putchar('\t');
	ft_putendl((char *)list->content);
}

void	ft_addhistory(char *str, t_params *params, int init)
{
	t_list	*new;
	int		fd;
	char	*home;
	char	*file;

	new = ft_lstnew(NULL, 0);
	new->content = ft_strdup(str);
	ft_lstadd(&params->history, new);
	if (!init)
	{
		home = ft_get_env_key("HOME", params->env);
		file = ft_strjoin(home, "/.21sh_history");
		if ((fd = open(file, O_APPEND | O_CREAT | O_WRONLY, 0600)) > 0)
		{
			ft_putendl_fd(str, fd);
			close(fd);
		}
	}
}

void	ft_load_history(t_params *params)
{
	char	*line;
	int		fd;
	char	*home;
	char	*file;

	home = ft_get_env_key("HOME", params->env);
	file = ft_strjoin(home, "/.21sh_history");
	if ((fd = open(file, O_RDONLY | O_CREAT, 0600)) > 0)
	{
		while (get_next_line(fd, &line) > 0)
			ft_addhistory(line, params, 1);
		close(fd);
	}
}
