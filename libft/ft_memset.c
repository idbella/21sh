/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 21:21:14 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/03 15:16:04 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			index;
	unsigned char	*str;
	unsigned char	cc;

	str = (unsigned char *)b;
	cc = (unsigned char)c;
	index = 0;
	while (index < len)
	{
		*str = cc;
		index++;
		str++;
	}
	return (b);
}
