/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 21:47:21 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/12 07:31:02 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		ft_is_aggregation(char *str)
{
	return (ft_strstr(str, ">&") || 0);
}

char	*ft_insert_str(char *str1, char *filler, int index)
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
	free(str1);
	return (result);
}

void	ft_split(char *str, t_params *params)
{
	int		i;
	int		start;
	int		qoute[2];
	char	*cmd;

	i = -1;
	qoute[0] = 0;
	qoute[1] = 0;
	start = 0;
	while (str[++i])
	{
		if (!qoute[0] && !qoute[1] && str[i] == ';')
		{
			cmd = ft_strsub(str, start, i - start);
			ft_parse(cmd, params);
			start = i + 1;
		}
		ft_qoutes(str[i], &qoute[0]);
		if (!str[i + 1] && str[i] != ';')
		{
			cmd = ft_strsub(str, start, i - start + 1);
			ft_parse(cmd, params);
		}
	}
	params->commands = ft_lstrev(params->commands);
}

int		ft_func1(int i, char *line)
{
	int i2;

	i2 = i;
	if (line[i] == '>' || line[i] == '<')
	{
		i2 = i - 1;
		while (i2)
		{
			if (ft_isspace(line[i2]))
				break ;
			if (!(line[i2] >= '0' && line[i2] <= '9'))
			{
				if (line[i] == '>' && line[i2] == '&')
				{
					if (i2 > 0 && line[i2 - 1] == '>')
					{
						/*  cmd >&1>file*/
						i2 = i;
						break;
					}
					if (i2 == i - 1)
						break ;
					i2++;
					break ;
				}
				i2 = i;
				break;
			}
			i2--;
		}
	}
	return (i2);
}

void	ft_fd_or_file(char **line, int i)
{
	int new_i;

	new_i = i + 1;
	if ((*line)[i] == '&')
	{
		if ((*line)[new_i] == '-' && ((*line)[new_i + 1] == ' ' || (*line)[new_i + 1] == '\0'))
			new_i ++;
		else
			while ((*line)[new_i])
			{
				if (ft_is_special_key((*line)[new_i]) || ft_isspace((*line)[new_i]))
					break;
				if (!ft_isdigit((*line)[new_i]))
				{
					new_i = i + 1;
					break ;
				}
				new_i++;
			}
	}
	*line = ft_insert_str(*line, " ", new_i);
}

int		ft_func2(int i, int i2, char **line)
{
	*line = ft_insert_str(*line, " ", i2);
	i++;
	while (ft_is_special_key((*line)[i + 1]))
		i++;
	if (ft_is_special_key((*line)[i]))
	{
		ft_fd_or_file(line, i);
		i++;
	}
	return (i);
}

int ft_is_token(char *str)
{
	int		i;
	int		qoute[2];

	i = 0;
	qoute[0] = 0;
	qoute[1] = 0;
	while (str[i])
	{
		ft_qoutes(str[i], qoute);
		if (!qoute[0] && !qoute[1] && ft_is_special_key(str[i]) && str[i] != '&')
			return (1);
		i++;
	}
	return (0);
}

char	**ft_get_args(char **args, int *i)
{
	int		start;
	int		count;
	char	**result;
	int		index;
	int		skip;
	int		i2;

	skip = 0;
	start = *i;
	i2 = *i;
	while (args[i2])
	{
		if (ft_is_token(args[i2]))
		{
			if (ft_is_aggregation(args[i2]))
				skip++;
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
	*i = i2 - start - 1;
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

int	ft_isvalid(char *str)
{
	int count1;
	int count2;
	int count3;

	count1 = 0;
	count3 = 0;
	count2 = 0;
	while (*str)
	{
		if (*str == '>')
			count1++;
		else if (*str == '<')
			count2++;
		else if (*str == '|')
			count3++;
		str++;
	}
	if (((count1 && count2) || (count1 && count3) || (count2 && count3)) || count1 > 2 || count2 > 2 || count3 > 1)
		return (0);
	return (1);
}

int		ft_countargs(char **args)
{
	int	count;

	count = 0;
	while(*args)
	{
		count++;
		args++;
	}
	return (count);
}

int		ft_is_redirection(char *str)
{
	if (ft_strstr(str, ">"))
		return (1);
	if (ft_strstr(str, ">>"))
		return (2);
	return (0);
}

int		ft_lex(char *str, t_list **lst)
{
	char		**commands;
	int 		i;
	t_list		*list;
	t_command	*command;
	t_outfile	*outfile;

	str = ft_remove_wsapces(str);
	commands = ft_strsplit(str, -1);
	i = 0;
	while (commands[i])
	{
		if (ft_is_token(commands[i]))
		{
			while (commands[i] && ft_strcmp(commands[i], "|"))
			{
				if (!ft_isvalid(commands[i]))
					return (0);
				if (ft_strequ(commands[i], ">") || ft_strequ(commands[i], ">>"))
				{
					if (!commands[i + 1] || ft_is_token(commands[i + 1]))
						return (0);
				}
				if (ft_is_redirection(commands[i]) && commands[i + 1] && !ft_is_token(commands[i + 1]))
				{
					if (command)
					{
						outfile = (t_outfile *)malloc(sizeof(t_outfile));
						outfile->name = ft_strdup(commands[i + 1]);
						outfile->open_mode = ft_is_redirection(commands[i]) == 1 ? O_APPEND|O_CREAT|O_WRONLY : O_CREAT|O_WRONLY|O_TRUNC;
						list = ft_lstnew(NULL, 0);
						list->content = outfile;
						ft_lstadd(&command->outlist, list);
					}
					i += 2;
					while (commands[i] && !ft_is_token(commands[i]))
						i++;
					i--;
				}
				if (ft_is_aggregation(commands[i]))
				{
					printf("::%s\n", commands[i]);
				}
				i++;
			}
			if (!commands[i] || ft_strcmp(commands[i], "|"))
				i--;
			else if (ft_strequ(commands[i], "|") && !commands[i + 1])
				return (0);
		}
		else
		{
			command = (t_command *)malloc(sizeof(t_command));
			list = ft_lstnew(NULL, 0);
			command->argv = ft_get_args(commands, &i);
			command->outlist = NULL;
			list->content = command;
			ft_lstadd(lst, list);
		}
		i++;
	}
	*lst = ft_lstrev(*lst);
	return (1);
}

void ft_parse(char *line, t_params *params)
{
	int		i;
	int		i2;
	int		qoute[2];
	t_list	*commands;
	t_list	*lst;

	i = -1;
	qoute[0] = 0;
	qoute[1] = 0;
	i2 = 0;
	while (line[++i])
	{
		if (!qoute[0] && !qoute[1] && ft_is_special_key(line[i]) && line[i] != '&')
		{
			i2 = ft_func1(i, line);
			i = ft_func2(i, i2, &line);
		}
		ft_qoutes(line[i], qoute);
	}
	commands = NULL;
	if (!ft_lex(line, &commands))
	{
		ft_putendl("21sh: parse error.");
		return ;
	}
	lst = ft_lstnew(NULL, 0);
	lst->content = commands;
	ft_lstadd(&params->commands, lst);
}