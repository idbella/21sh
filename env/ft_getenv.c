/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 00:33:37 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/12 22:44:25 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

char	**ft_get_env(t_list *list)
{
	char	**env_str;
	t_env	*env;
	char	*entry;
	int		index;

	env = NULL;
	if (!(env_str = (char **)malloc(sizeof(char *) * ft_lstcount(list) + 1)))
		return (NULL);
	index = 0;
	while (list)
	{
		env = (t_env *)list->content;
		entry = ft_strjoin(env->key, "=");
		env_str[index] = ft_strjoin(entry, env->value);
		free(entry);
		list = list->next;
		index++;
	}
	env_str[index] = NULL;
	return (env_str);
}
