/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 09:24:39 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/23 22:39:18 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include "../ft_21sh.h"
# define C_UP 4283163
# define C_DOWN 4348699
# define C_RIGHT 4414235
# define C_LEFT 4479771
# include <sys/ioctl.h>
void	setup()
{
	char	*term	= getenv("TERM");
	char	buff[2048];
	tgetent(buff, term);
	struct termios termio;
	tcgetattr(0, &termio);
	termio.c_lflag = ~ICANON & termio.c_lflag;
	termio.c_lflag = ~ECHO & termio.c_lflag;
	tcsetattr(0, TCSANOW, &termio);
}

int	ft_get_width()
{
	struct winsize size;
	ioctl(0, TIOCGWINSZ, &size);
	return (size.ws_col);
}

void	ft_cursor(int dir,int *pos, int len)
{
	if (dir == C_LEFT)
		(*pos)++;
	else
		(*pos)--;
	if (*pos < 0)
		*pos = 0;
	if (*pos > len)
		*pos = len;
}

int	ft_put(int c)
{
	ft_putchar_fd(c, 0);
	return (c);
}

void ft_mv_cursor(int pos, int ret)
{
	char	*mv_left;
	char	*mv_down;

	mv_left = tgetstr("le", NULL);
 	mv_down = tgetstr("do", NULL);
	 while (pos-- > 0)
	 	tputs(mv_left, 0, ft_put);
	if(ret)
	{
		tputs(mv_down, 0, ft_put);
		ft_putchar_fd('\r', 0);
	}
}

void	ft_clearline(int len, int width, int c)
{
	char *del;
	char *up;
	int count;

	del = tgetstr("dl", NULL);
	up = tgetstr("up", NULL);
	tputs(del, 1, ft_put);
	ft_putchar_fd('\r', 0);
	count = len / width;
	if (c && len % width == 0)
	{

	 	system("echo test >>file");
		 count--;
	}
	/*else if (!c && len % width == 0)
		count++;
	*/
	char *s = ft_strjoin("echo 'lines = ", ft_itoa(count));
	system(ft_strjoin(s, "'>>file"));
	while (count > 0)
	{
		tputs(up, 1, ft_put);
		tputs(del, 1, ft_put);
		ft_putchar_fd('\r', 0);
		count--;
	}
}

void ft_print(char *line, int pos, int c)
{
	char *mv_left;
	int len;
	int width = ft_get_width();
	
	len = ft_strlen(line) + ft_strlen(NAME);
	ft_clearline(len , width, c);
	ft_putstr_fd(NAME, 0);
	ft_putstr_fd(line, 0);
	ft_mv_cursor(pos, len%width == 0);
}


char		*ft_backspace(char *str, int pos)
{
	int		len;
	int		index;

	len = ft_strlen(str);
	if (len)
	{
		index = len - pos - 1;
		if (index >= 0)
			str = ft_delchar(&str, index);
	}
	return (str);
}

static char	*ft_strinsert(char *str1, char *filler, int index)
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
	return (result);
}

int main()
{
	
	int c;
	int cursor_pos;
	char *line;
	cursor_pos = 0;
	line = ft_strnew(0);
	setup();
	c = 0;
	ft_putstr(NAME);
	while(read(0, &c, 4))
	{
		if (c == 127)
		{
			line = ft_backspace(line, cursor_pos);
			ft_print(line, cursor_pos, 0);
		}
		else
		{
			if (c == C_LEFT || c == C_RIGHT)
				ft_cursor(c, &cursor_pos, ft_strlen(line));
			else if (ft_isprint(c))
			{
				int len = ft_strlen(line) - cursor_pos;
				if (len >= 0)
				{
					char s[2];
					s[0] = c;
					s[1] = '\0';
					line = ft_strinsert(line, s, ft_strlen(line) - cursor_pos);
				}
			}
			ft_print(line, cursor_pos, 1);
		}
		c = 0;
	}
}

/*
 1 2 3 4 5 6 7 
_______________
|$> cmd1 -flag|
|-flag -flag  |
|_____________|
*/
