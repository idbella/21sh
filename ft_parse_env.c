/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 00:33:37 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/12 05:24:03 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_parse_env(char **env, t_params *params)
{
	int		index;
	char	*key;
	char	*value;
	int		i;

	index = 0;
	while (env[index])
	{
		i = 0;
		while (env[index][i])
		{
			if (env[index][i] == '=')
			{
				key = ft_strsub(env[index], 0, i++);
				break ;
			}
			i++;
		}
		value = ft_strsub(env[index], i, ft_strlen(env[index]));
		ft_setenv(key, value, params);
		free(key);
		free(value);
		index++;
	}
	params->env = ft_lstrev(params->env);
}
