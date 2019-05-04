/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 21:47:53 by sid-bell          #+#    #+#             */
/*   Updated: 2019/05/04 19:36:53 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_21SH_H
# define FT_21SH_H
# include "libft/libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <termios.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termcap.h>
# include <signal.h>
# define APPEND O_APPEND|O_CREAT|O_WRONLY
# define TRUNC O_CREAT|O_WRONLY|O_TRUNC
# define DELEMITER -1
# define QOUTE_MARK -2
# define ESC_NEWLINE -3
# define ESC_SLASH -4
# define ESC_QOUTE -5
# define ESC_DQOUTE -6
# define ESC_TAB -7
# define ESC_VTAB -8
# define ESC_SPACE -9
typedef struct stat	t_stat;
typedef struct	s_command
{
	char	**argv;
	t_list	*outlist;
	char	*heredoc;
}				t_command;
typedef struct s_alias
{
	char *key;
	char *value;
}				t_alias;
typedef struct	s_outfile
{
	char		*name;
	int			open_mode;
	int			fd_src;
	int			fd_dest;
	int			close;
}				t_outfile;
typedef struct s_tc
{
    int             x;
    int             y;
    int             sw;
    int             sh;
    int             sitext;
    int             setext;
    char            *text;
    int             khistory;
    t_list          *history;
    struct termios  termi;
}              t_tc;
typedef  struct s_tcline
{
    char            *line;
    int             len;
    int             cursor;
    struct s_tcline *next;
    struct s_tcline *prev;
}               t_tcline;
typedef struct	s_params
{
	t_list		*env;
	t_list		*commands;
	int			savedfd[3];
	int			pipefd[2];
	int			currentfd[3];
	int			pid;
	struct termios *term;
	int			err;
	char		*pwd;
	t_list		*history;
	int			history_pos;
	t_tc		**ptermcap;
	t_tcline	**pline;
	char		heredoc;
	char		quate;
	char		ctrlc;
	char		waiting;
	char		*newcmd;
}				t_params;

typedef struct		s_env
{
	char			*key;
	char			*value;
}					t_env;
t_params		params;
void			ft_env(t_list *list);
char			*ft_get_env_key(char *key, t_list *list);
char			**ft_get_env(t_list *list);
void			ft_parse_env(char **env, t_params *params);
void			ft_setenv(char *key, char *value, t_params *params);
void			ft_unsetenv(char *key, t_params *params);
void			ft_parse(char *line, t_params *params);
char			*ft_delchar(char *str, int index);
char			*ft_insertchar(char **src, char c, int index);
char			*ft_joinargs(char *str);
void			ft_handle_qoutes(char **line, t_params *params);
void			ft_split(char *line, t_params *params);
void			ft_qoutes(char c, char *qoute);
int				ft_is_special_key(char c);
char			*ft_remove_wsapces(char *str);
int				ft_isbuilt_in(char *name);
void			ft_built_in(t_command *cmd, t_params *params);
void			ft_echo(t_command *cmd);
void			ft_exec(t_params *params, t_list *commands);
void    		ft_init_exec(t_params *params);
void			ft_init(t_params *params, char **env, char **argv, char **text);
int 			ft_is_token(char *str);
char			*ft_insert_str(char *str1, char *filler, int index);
void			ft_split(char *str, t_params *params);
char			**ft_get_args(t_command *cmd, char **args, int *i, t_params *params);
int				ft_is_aggregation(char *current, char *next);
int				ft_get_fd_src(char *str);
int				ft_get_fd_dest(char *str);
int				ft_isvalidred(char *str);
int				ft_is_redirection(char *str);
int				ft_lex(char *str, t_params *params);
void			ft_fd_or_file(char **line, int i);
char			*ft_find_file(char *file, t_list *list);
char			**ft_getpaths(t_list *list);
t_stat			*ft_exist(char *file);
void			ft_addfile(t_command *command, char **commands, int i);
void			ft_addaggr(t_command *command, char *cmd, char *next);
int     		ft_get_redirections(char **commands, t_command *command, int i, t_params *params);
char    		**ft_lst_to_arr(t_list *list);
char			*ft_strinsert(char *str1, char *filler, int index);
char			*ft_here_doc(char *eof, t_params *params);
int				ft_get_io_red(t_command *cmd, t_params *params);
int				ft_run(t_params *params, t_command *cmd);
int				ft_check(char **commands, int i);
void			ft_free_list(t_list *list);
char			**ft_getcommands(char *str);
int	ft_addcmd(t_command *command, char **commands,
						t_params *params, int *i);
void			ft_sig_win_handler(int sig_num);
void			ft_sig_int_handler(int sig);
void			ft_print_path(t_params *params);
/*
**
*/
char	*read_line(t_params *params);

int				ft_is_qoute(char c);
void			ft_escape(char **str);
void			ft_unescape(char *str);
void			ft_cd(char *location, t_params *params);
char			*ft_pwd(void);
char			*ft_find_in_path(char *part0, t_params *params);
char			*ft_find_in_dir(char *path, char *part0);
int				ft_is_exec(char *file, char *path);
char			*ft_gethome(char *str, t_params *params);
char			*ft_replace_char(char *str1, char *filler, int index);
char			*ft_strcut(char *str, int i0, int i1);
char			*ft_getvars(char *str, t_params *params);
void			ft_load_history(t_params *params);
void			ft_history(t_list *list);
char			*ft_remove_qoutes(char *str);
/*
** 
*/
void			ft_free_cmd_list(t_list *list);
void			ft_free_tab(char **arr);
#endif
