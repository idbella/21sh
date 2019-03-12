/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 21:47:53 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/12 05:36:12 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_21SH_H
# define FT_21SH_H
# include "libft/libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct	s_command
{
	char	**argv;
	t_list	*outlist;
}				t_command;

typedef struct	s_outfile
{
	char		*name;
	int			open_mode;
	int			fd;
}				t_outfile;

typedef struct	s_params
{
	t_list			*env;
	t_list		*commands;
	int			savedfd[2];
	int			pipefd[2];
	int			currentfd[2];
	char		*infile;
	int			pid;
}				t_params;
typedef struct		s_env
{
	char			*key;
	char			*value;
}					t_env;
void			ft_env(t_list *list);
char			*ft_get_env_key(char *key, t_list *list);
char			**ft_get_env(t_list *list);
void			ft_parse_env(char **env, t_params *params);
void			ft_setenv(char *key, char *value, t_params *params);
void			ft_unsetenv(char *key, t_params *params);
void			ft_parse(char *line, t_params *params);
char			*ft_delchar(char **str, int index);
char			*ft_insertchar(char **src, char c, int index);
char			*ft_joinargs(char *str);
void			ft_handle_qoutes(char **line);
void			ft_split(char *line, t_params *params);
void			ft_qoutes(char c, int *qoute);
int				ft_is_special_key(char c);
char			*ft_remove_wsapces(char *str);
int				ft_isbuilt_in(char *name);
void			ft_built_in(t_command *cmd, t_params *params);
void			ft_echo(t_command *cmd);
void			ft_exec(t_params *params, t_list *commands);
void    		ft_init_exec(t_params *params);
#endif
