/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 00:33:37 by sid-bell          #+#    #+#             */
/*   Updated: 2019/04/01 17:16:38 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

static void	ft_helper1(char *new)
{
	ft_putendl(new);
	ft_putendl("Permission denied");
	free(new);
}

static void	ft_helper2(char *old, char *new, t_params *params)
{
	char	*dir;

	if (new[0] != '/')
		dir = ft_pwd();
	else
		dir = ft_strdup(new);
	ft_setenv("OLDPWD", old, params);
	ft_setenv("PWD", dir, params);
	free(params->pwd);
	params->pwd = ft_strdup(dir);
	free(dir);
}

void		ft_changedir(char *dir, t_params *params)
{
	char *old;
	char *new;

	if (access(dir, X_OK))
	{
		ft_putendl_fd("Permission denied", 2);
		return ;
	}
	old = params->pwd;
	new = ft_strdup(dir);
	if (chdir(new))
	{
		ft_helper1(new);
		return ;
	}
	else
		ft_helper2(old, new, params);
	free(new);
}

void		ft_helper(char *dir, t_stat *stat, t_params *params)
{
	if (S_ISDIR(stat->st_mode))
	{
		ft_changedir(dir, params);
	}
	else
	{
		ft_putstr(dir);
		ft_putendl(": Not a directory.");
	}
}

void		ft_cd(char *location, t_params *params)
{
	char	*dir;
	t_stat	*stat;

	if (location && !ft_strcmp(location, "-"))
		dir = ft_get_env_key("OLDPWD", params->env);
	else if (!location)
		dir = ft_get_env_key("HOME", params->env);
	else
		dir = ft_strdup(location);
	dir = dir ? dir : ft_strnew(0);
	if ((stat = ft_exist(dir)))
	{
		ft_helper(dir, stat, params);
		free(stat);
	}
	else
	{
		ft_putstr(dir);
		ft_putendl(": No such file or directory");
	}
	free(dir);
}
