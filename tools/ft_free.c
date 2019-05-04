/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 22:05:28 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/04 21:16:53 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

void	ft_free_io_list(t_list *list)
{
	t_outfile	*lst;

	while (list)
	{
		lst = (t_outfile *)list->content;
		if (lst->name)
			free(lst->name);
		list = list->next;
	}
}

void	ft_free_tab(char **arr)
{
	int i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (arr)
		free(arr);
}

void	ft_free_cmd_list(t_list *list)
{
	t_command	*commnd;
	t_list		*lst;

	while (list)
	{
		commnd = (t_command *)list->content;
		ft_free_tab(commnd->argv);
		ft_free_io_list(commnd->outlist);
		lst = list;
		list = list->next;
		free(lst);
	}
}

void	ft_free_list(t_list *list)
{
	t_list *lst;

	while (list)
	{
		lst = list;
		list = list->next;
		free(lst);
	}
}
