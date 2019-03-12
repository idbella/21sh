/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 22:15:52 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/12 22:42:07 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int	ft_get_fd_src(char *str)
{
	int 	i;
	char	*fd;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			break ;
        i++;
	}
	if (i == 0)
		return (1);
	fd = ft_strsub(str, 0, i);
	i = ft_atoi(fd);
	free(fd);
	return (i);	
}

int	ft_get_fd_dest(char *str)
{
	int 	i;
	char	*fd;

	i = 0;
	if ((fd = ft_strrchr(str, '&')))
		fd++;
	else
		printf("Unexpected Error : %s\n", str);
	if (ft_isdigit(fd[0]))
	{
		i = ft_atoi(fd);
	}
	return (i);	
}
