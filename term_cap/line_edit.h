/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amassnao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 19:25:57 by amassnao          #+#    #+#             */
/*   Updated: 2019/05/01 19:27:44 by amassnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_EDIT_H
# define LINE_EDIT_H
# include <unistd.h>
# include <stdio.h>
# include <curses.h>
# include <term.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include "../libft/libft.h"
# include "../ft_21sh.h"

int			ft_putcharc(int c);
void		rawmode(t_tc *list);
void		getxy(t_tc *list);
t_tc		*init();
t_tcline	*setlines(char *content);
void		movecursor(t_tc *list, int x, int y);
void		up(t_tc *list);
void		down(t_tc *list);
void		left(t_tc *list, t_tcline **line);
void		right(t_tc *list, t_tcline **line);
char		*joinchar(char **base, char extend, int index, int mode);
char		*read_setup(t_params *params);
void		read_key(t_tc *list, t_tcline **line, t_params *params);
int			ft_iskey(char *buffer, int key, int kkey, int kkkey);
t_tcline	*ft_puttext(t_tc *list, t_tcline *line, char *buffer);
int			isnespace(t_tc *list, t_tcline *line);
void		previewword(t_tc *list, t_tcline **line);
void		nextword(t_tc *list, t_tcline **line);
void		gobegin(t_tc *list, t_tcline **line);
void		goend(t_tc *list, t_tcline **line);
void		selectext(t_tc *list, t_tcline **line);
void		reverselectext(t_tc *list, t_tcline **line);
void		copy(t_tc *list, t_tcline **line, int mode);
void		past(t_tc *list, t_tcline *line);
void		clearselect(t_tc *list, t_tcline **line);
void		deletchar(t_tc *list, t_tcline **line, char *buffer);
void		putlines(t_tc *list, t_tcline **pline);
void		prevline(t_tc *list, t_tcline **line);
void		nextline(t_tc *list, t_tcline **line);
void		fixlines(t_tc *list, t_tcline *line);
void		deleteline(t_tc *list, t_tcline *line);
char		*migratelines(t_tcline *line);
void		history_up(t_tc *list, t_tcline **line, t_params *params);
void		history_down(t_tc *list, t_tcline **line, t_params *params);
void		addtohistory(t_params *list, char *cmd);
void		gotoend(t_tc *list, t_tcline **line);
void		completecmd(t_tc *list, t_tcline *line);
#endif
