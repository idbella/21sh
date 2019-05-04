/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isredirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 18:30:45 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/04 18:30:59 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

int			ft_is_redirection(char *str)
{
	if (ft_strstr(str, ">>"))
		return (2);
	if (ft_strstr(str, ">"))
		return (1);
	if (ft_strstr(str, "<"))
		return (3);
	return (0);
}
