/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 00:33:37 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/03 20:47:47 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

int			valid_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char		*ft_getvarname(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!valid_char(str[i]))
			break ;
		i++;
	}
	return (ft_strsub(str, 0, i));
}

static int	ft_helper(char **result, t_params *params, char *key, int i)
{
	char *nv;

	if (!(nv = ft_get_env_key(key, params->env)))
		nv = ft_strnew(0);
	*result = ft_strcut(*result, i + 1, i + ft_strlen(key) + 1);
	*result = ft_replace_char(*result, nv, i);
	i += ft_strlen(nv) - 1;
	free(nv);
	return (i);
}

char		*ft_getvars(char *str, t_params *params)
{
	int		i;
	char	*key;
	int		qoute;
	char	*result;

	i = -1;
	qoute = 0;
	result = ft_strdup(str);
	while (result[++i])
	{
		if (!qoute && result[i] == '$')
		{
			if ((key = ft_getvarname(result + i + 1)))
			{
				i = ft_helper(&result, params, key, i);
				free(key);
			}
		}
		if (result[i] == '\'')
			qoute = !qoute;
	}
	return (result);
}
