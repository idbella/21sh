/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_in_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 00:33:37 by sid-bell          #+#    #+#             */
/*   Updated: 2019/04/01 02:52:15 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

char	*ft_find_in_dir(char *path, char *part0)
{
	DIR				*dir;
	struct dirent	*entry;

	if ((dir = opendir(path)))
	{
		while ((entry = readdir(dir)))
		{
			if (entry->d_name[0] == '.')
				continue ;
			if (!ft_strncmp(part0, entry->d_name, ft_strlen(part0)))
			{
				closedir(dir);
				return (ft_strdup(entry->d_name));
			}
		}
		closedir(dir);
	}
	return (NULL);
}
