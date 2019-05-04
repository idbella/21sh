/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gethome.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 00:33:37 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/03 20:25:52 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

char	*ft_replace_char(char *str1, char *filler, int index)
{
	char	*result;
	char	*part1;
	char	*part2;
	int		len;

	len = ft_strlen(str1);
	part1 = ft_strsub(str1, 0, index);
	part2 = ft_strsub(str1, index + 1, len - index);
	result = ft_strjoin(part1, filler);
	free(part1);
	part1 = result;
	result = ft_strjoin(result, part2);
	free(part1);
	free(part2);
	free(str1);
	return (result);
}

char	*ft_gethome(char *str, t_params *params)
{
	int		i;
	int		qoute;
	char	*nv;
	char	*result;

	qoute = 0;
	i = 0;
	result = ft_strdup(str);
	if (!(nv = ft_get_env_key("HOME", params->env)))
		nv = ft_strnew(0);
	while (result[i])
	{
		if (!qoute && result[i] == '~' &&
			((i > 0 && (ft_isspace(result[i - 1]) ||
				ft_is_special_key(result[i - 1]))) || i == 0))
		{
			result = ft_replace_char(result, nv, i);
			i += ft_strlen(nv) - 1;
		}
		else if (result[i] == '\"')
			qoute = !qoute;
		i++;
	}
	free(nv);
	return (result);
}
