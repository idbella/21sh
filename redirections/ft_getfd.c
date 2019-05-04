/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 22:15:52 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/02 22:36:38 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

int	ft_get_fd_src(char *str)
{
	int		i;
	char	*fd;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			break ;
		i++;
	}
	if (i == 0)
		return (ft_strchr(str, '>') ? 1 : 0);
	fd = ft_strsub(str, 0, i);
	i = ft_atoi(fd);
	free(fd);
	return (i);
}

int	ft_get_fd_dest(char *str)
{
	int		i;

	i = 0;
	if (ft_strrchr(str, '&'))
	{
		str = ft_strrchr(str, '&') + 1;
	}
	if (ft_isdigit(str[0]))
	{
		i = ft_atoi(str);
	}
	else
		return (-1);
	return (i);
}
