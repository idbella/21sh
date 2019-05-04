/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 00:33:37 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/04 21:50:47 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

void		ft_free_paths(char **paths)
{
	int i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

static char	*ft_helper1(char **paths, char *file)
{
	t_stat *stat;

	if (paths)
		ft_free_paths(paths);
	if ((stat = ft_exist(file)))
	{
		free(stat);
		return (ft_strdup(file));
	}
	return (NULL);
}

int			ft_helper2(char **paths, char *file)
{
	t_stat *stat;

	if ((stat = ft_exist(file)))
	{
		if (paths)
			ft_free_paths(paths);
		free(stat);
		return (1);
	}
	return (0);
}

char		*ft_find_file(char *file, t_list *list)
{
	char	**paths;
	int		index;
	char	*fullpath;
	char	*tmp;

	index = -1;
	paths = ft_getpaths(list);
	if ((!ft_strchr(file, '/') && paths))
	{
		while (paths[++index])
		{
			fullpath = ft_strjoin(paths[index], "/");
			tmp = fullpath;
			fullpath = ft_strjoin(fullpath, file);
			free(tmp);
			if (ft_helper2(paths, fullpath))
				return (fullpath);
			free(fullpath);
		}
		ft_free_paths(paths);
		return (NULL);
	}
	else
		return (ft_helper1(paths, file));
}

t_stat		*ft_exist(char *file)
{
	t_stat	*fstat;

	if (!(fstat = (t_stat *)malloc(sizeof(t_stat))))
		return (NULL);
	if (!stat(file, fstat))
		return (fstat);
	free(fstat);
	return (NULL);
}
