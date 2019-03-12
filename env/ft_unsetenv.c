/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 00:33:37 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/12 22:44:38 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

static void	ft_helper(char *key, t_list **new, t_params *params)
{
	t_env	*env;
	t_list	*elem;
	t_list	*tmp;

	env = (t_env *)params->env->content;
	if (!ft_strcmp(env->key, key))
	{
		free(env->key);
		free(env->value);
		free(env);
		elem = params->env->next;
		free(params->env);
		params->env = elem;
	}
	else
	{
		elem = ft_lstnew(NULL, 0);
		elem->content = env;
		ft_lstadd(new, elem);
		tmp = params->env;
		params->env = params->env->next;
		free(tmp);
	}
}

void		ft_unsetenv(char *key, t_params *params)
{
	t_list	*new;

	new = NULL;
	if (!key)
	{
		ft_putendl_fd("unsetenv: Too few arguments.", 2);
		return ;
	}
	while (params->env)
	{
		ft_helper(key, &new, params);
	}
	params->env = new;
}
