/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 22:10:05 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/16 06:08:27 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	**ft_get_args(t_command *cmd, char **args, int *i)
{
	int			start;
	int			count;
	char		**result;
	int			index;
	int			skip;
	int			i2;
	t_outfile	*outfile;
	t_list 		*list;

	skip = 0;
	start = *i;
	i2 = *i;
	while (args[i2])
	{
		if (ft_is_token(args[i2]))
		{
			if (!ft_isvalidred(args[i2]))
				return (NULL);
			if (ft_is_aggregation(args[i2]))
			{
				if (cmd)
				{
					outfile = (t_outfile *)malloc(sizeof(t_outfile));
					outfile->fd_src = ft_get_fd_src(args[i2]);
					outfile->fd_dest = ft_get_fd_dest(args[i2]);
					outfile->name = NULL;
					if (outfile->fd_dest == -1)
							outfile->name = ft_strdup("/dev/null");
					list = ft_lstnew(NULL, 0);
					list->content = outfile;
					ft_lstadd(&cmd->outlist, list);
				}
				skip++;
			}
			else
				break;
		}
		i2++;
	}
	count = i2 - start - skip;
	if (count <= 0)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * count + 1);
	index = 0;
	*i += i2 - start - 1;
	while (start < i2)
	{
		if (!ft_is_aggregation(args[start]))
		{
			result[index] = args[start];
			index++;
		}
		start++;
	}
	result[index] = NULL;
	return (result);
}
