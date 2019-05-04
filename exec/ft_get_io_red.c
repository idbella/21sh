/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_io_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:05:05 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/03 15:02:05 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_21sh.h"

static int	ft_get_aggr(t_params *params, t_outfile *outfile)
{
	int			src;
	int			dst;

	src = outfile->fd_src;
	dst = outfile->fd_dest;
	if (src < 0 || src > 2)
		return (src);
	if (dst < 0 || dst > 2)
		return (dst);
	if (outfile->fd_src == 1 || outfile->fd_src == 2)
		src = params->currentfd[outfile->fd_src];
	if (outfile->fd_dest == 1 || outfile->fd_dest == 2)
		dst = params->currentfd[outfile->fd_dest];
	dup2(dst, src);
	return (0);
}

int ft_get_io_red(t_command *cmd, t_params *params)
{
	char		*file;
	t_outfile	*outfile;
	t_list		*list;
	int			src;
	int			err;

	cmd->outlist = ft_lstrev(cmd->outlist);
	list = cmd->outlist;
	while (list)
	{
		outfile = (t_outfile *)list->content;
		file = outfile->name;
		if (file)
		{
			if (outfile->open_mode != O_RDONLY || ft_exist(file))
			{
				src = open(file, outfile->open_mode, 0777);
				if ((outfile->fd_src >= 0 && outfile->fd_src <= 2))
				{
					if (outfile->fd_src == 0)
					{
						if (outfile->open_mode == O_RDONLY)
						{
							dup2(src, 0);
							close(src);
						}
						else
							close(0);
					}
					params->currentfd[outfile->fd_src] = src;
				}
				if (src < 0)
				{
					ft_printf_fd(params->savedfd[2],
						"21sh: permission denied: %s\n", file);
					break ;
				}
			}
			else
			{
				ft_printf_fd(1, "21sh: no such file or directory: %s\n", file);
				close(params->currentfd[1]);
				params->currentfd[1] = -1;
				break ;
			}
		}
		if (!file)
		{
			if ((err = ft_get_aggr(params, outfile)))
				return (err);
		}
		list = list->next;
	}
	return (0);
}
