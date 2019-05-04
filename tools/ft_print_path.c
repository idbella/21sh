/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 19:26:00 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/04 19:26:59 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

char	*ft_getpath(t_list *list, t_params *params)
{
	char	*cwd;
	char	*home;
	char	*tmp;

	cwd = ft_strdup(params->pwd);
	if ((home = ft_get_env_key("HOME", list)))
	{
		tmp = cwd;
		if (ft_strequ(home, cwd))
		{
			cwd = ft_strdup("~/");
			free(tmp);
		}
		else if (ft_strncmp(cwd, home, ft_strlen(home)) == 0)
		{
			cwd = ft_strsub(cwd, ft_strlen(home), ft_strlen(cwd));
			free(tmp);
			tmp = cwd;
			cwd = ft_strjoin("~", cwd);
			free(tmp);
		}
		free(home);
	}
	return (cwd);
}

void	ft_print_path(t_params *params)
{
	char *cwd;

	cwd = ft_getpath(params->env, params);
	ft_printf_fd(1, "\x1B[32m%s\x1b[0m$>\n", cwd);
	free(cwd);
}
