/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_or_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 22:12:42 by sid-bell          #+#    #+#             */
/*   Updated: 2019/04/01 22:13:32 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

void	ft_fd_or_file(char **line, int i)
{
	int new_i;

	new_i = i + 1;
	if ((*line)[i] == '&')
	{
		if ((*line)[new_i] == '-' && ((*line)[new_i + 1] == ' ' || (*line)[new_i + 1] == '\0'))
			new_i ++;
		else
			while ((*line)[new_i])
			{
				if (ft_is_special_key((*line)[new_i]) || ft_isspace((*line)[new_i]))
					break;
				if (!ft_isdigit((*line)[new_i]))
				{
					new_i = i + 1;
					break ;
				}
				new_i++;
			}
	}
	*line = ft_insert_str(*line, " ", new_i);
}
