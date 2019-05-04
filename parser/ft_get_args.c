/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 22:10:05 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/04 18:27:02 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

char	*ft_trim(char **str)
{
	int		len;
	char	*st;
	char	*tmp;

	st = *str;
	len = ft_strlen(st);
	if (len > 1 && (*st == '\'' || *st == '\"') && st[len - 1] == *st)
	{
		tmp = *str;
		*str = ft_strsub(*str, 1, len - 2);
		free(tmp);
	}
	return (*str);
}

char	*ft_remove_qoutes(char *str)
{
	char	**parts;
	int		i;
	char	*tmp;

	if (ft_strchr(str, -2))
	{
		if ((parts = ft_strsplit(str, -2)) && parts[0])
		{
			i = 0;
			str = ft_trim(&parts[0]);
			while (parts[i + 1])
			{
				tmp = str;
				str = ft_strjoin(str, ft_trim(&parts[i + 1]));
				i++;
				free(tmp);
				free(parts[i + 1]);
			}
			free(parts[0]);
			free(parts);
		}
	}
	else
		str = ft_trim(&str);
	return (str);
}

void	ft_add(t_list **list, char **args, int i)
{
	t_list *new;

	new = ft_lstnew(NULL, 0);
	new->content = ft_remove_qoutes(ft_strdup(args[i]));
	ft_unescape(new->content);
	ft_lstadd(list, new);
}

char	**ft_get_args(t_command *cmd, char **args, int *i, t_params *params)
{
	t_list		*list;

	list = NULL;
	while (args[*i])
	{
		if (ft_is_token(args[*i]))
		{
			if (ft_strequ(args[*i], "|"))
				break ;
			if (!ft_isvalidred(args[*i]) ||
				(*i = ft_get_redirections(args, cmd, *i, params)) < 0)
			{
				ft_free_list(list);
				return (NULL);
			}
		}
		else
			ft_add(&list, args, *i);
		(*i)++;
	}
	if (!ft_strequ(args[*i], "|"))
		(*i)--;
	list = ft_lstrev(list);
	return (ft_lst_to_arr(list));
}
