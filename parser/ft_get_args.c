/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 22:10:05 by sid-bell          #+#    #+#             */
/*   Updated: 2019/04/02 08:36:35 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

char	**ft_get_args(t_command *cmd, char **args, int *i, t_params *params)
{
	t_list 		*list;
	t_list		*new;

	list = NULL;
	while (args[*i])
	{
		if (ft_is_token(args[*i]))
		{
			if (ft_strequ(args[*i], "|"))
				break ;
			if ((*i = ft_get_redirections(args, cmd, *i, params)) < 0)
			{
				// free list here
				return (NULL);
			}
		}
		else
		{
			new = ft_lstnew(NULL, 0);
			new->content = ft_strdup(args[*i]);
			ft_lstadd(&list, new);
		}
		(*i)++;
	}
	if (!ft_strequ(args[*i], "|"))
		(*i)--;
	list = ft_lstrev(list);
	return (ft_lst_to_arr(list));
}
