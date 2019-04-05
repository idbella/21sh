/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 18:38:24 by sid-bell          #+#    #+#             */
/*   Updated: 2019/04/05 13:42:21 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

void    ft_show_aliases(t_list *list)
{
	t_alias *alias;

	while (list)
	{
		alias = (t_alias *)list->content;
		ft_printf_fd(1, "%s=%s\n", alias->key, alias->value);
		list = list->next;
	}
}

void    ft_alias(char **args, t_params *params)
{
	t_list 	*list;
	t_alias	alias;
	char	**parts;

	if (args[1])
	{
		
		if (ft_strpos(args[1], "=") > 0)
		{
			parts = ft_strsplit(args[1], '=');
			alias.key = parts[0];
			if (parts[1] != NULL)
			{
				alias.value = parts[1];
				list = ft_lstnew(&alias, sizeof(t_alias));
				ft_lstadd(&params->alias, list);
			}
			else
				ft_putendl("21sh : bad assignment");
		}
		else
			ft_putendl("21sh : bad assignment");
	}
	else
		ft_show_aliases(params->alias);
}

char	*ft_get_alias(char *cmd, t_list *list)
{
	t_alias *alias;

	while (list)
	{
		alias = (t_alias *)list->content;
		if (ft_strequ(alias->key, cmd))
			return (ft_strdup(alias->value));
		list = list->next;
	}
	return (NULL);
}
