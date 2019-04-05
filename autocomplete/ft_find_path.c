/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 00:33:37 by sid-bell          #+#    #+#             */
/*   Updated: 2019/04/01 02:48:55 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

void	ft_free(char ***str)
{
	char	**ptr;
	int		i;

	i = 0;
	ptr = *str;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

char	*ft_find_in_path(char *part0, t_params *params)
{
	char			**paths;
	int				i;
	char			*file;

	if ((paths = ft_getpaths(params->env)))
	{
		i = 0;
		while (paths[i])
		{
			if ((file = ft_find_in_dir(paths[i], part0)))
			{
				if (ft_is_exec(file, paths[i]))
				{
					ft_free(&paths);
					return (file);
				}
				free(file);
			}
			i++;
		}
		ft_free(&paths);
	}
	return (NULL);
}
