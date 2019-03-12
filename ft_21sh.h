/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 21:47:53 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/11 20:41:17 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_21SH_H
# define FT_21SH_H
# include "libft/libft.h"
# include <stdio.h>

typedef struct	s_command
{
	char	**argv;
	t_list	*outfile;
}				t_command;

typedef struct	s_outfile
{
	char		*name;
	int			open_mode;
	int			fd;
}				t_outfile;

typedef struct	s_params
{
	t_list	*commands;
}				t_params;

void			ft_parse(char *line, t_params *params);
char			*ft_delchar(char **str, int index);
char			*ft_insertchar(char **src, char c, int index);
char			*ft_joinargs(char *str);
void			ft_handle_qoutes(char *line, t_params *params);
void			ft_split(char *line, t_params *params);
void			ft_qoutes(char c, int *qoute);
int				ft_is_special_key(char c);
char			*ft_remove_wsapces(char *str);

#endif
