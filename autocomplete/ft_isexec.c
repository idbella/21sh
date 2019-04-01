/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isexec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 00:33:37 by sid-bell          #+#    #+#             */
/*   Updated: 2019/04/01 02:49:22 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

int		ft_is_exec(char *file, char *path)
{
	t_stat		state;
	int			val;

	val = 0;
	path = ft_strjoin(path, "/");
	file = ft_strjoin(path, file);
	if (!stat(file, &state))
	{
		if (S_ISREG(state.st_mode) && !access(file, X_OK))
			val = 1;
	}
	free(path);
	free(file);
	return (val);
}
