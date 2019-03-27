/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clearline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 11:12:54 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/26 11:13:11 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

void	ft_clearline(t_line *line)
{
	int count;
	int	current;
	int i;

	count = ft_get_nline(line);
	current = ft_get_cline(line);
	i = 1;
	while (i < current)
	{
		tputs(line->mv_up, 1, ft_put);	
		i++;
	}
	i = 0;
	while (i < count)
	{
		tputs(line->delete, 1, ft_put);
		ft_putchar_fd('\r', 0);
		i++;
	}
}
