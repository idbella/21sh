/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 21:45:12 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/25 19:08:22 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

char	*ft_insert_str(char *str1, char *filler, int index)
{
	char	*result;
	char	*part1;
	char	*part2;
	int		len;

	len = ft_strlen(str1);
	part1 = ft_strsub(str1, 0, index);
	part2 = ft_strsub(str1, index, len - index);
	result = ft_strjoin(part1, filler);
	free(part1);
	part1 = result;
	result = ft_strjoin(result, part2);
	free(part1);
	free(part2);
	free(str1);
	return (result);
}
