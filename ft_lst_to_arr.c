/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 09:08:56 by sid-bell          #+#    #+#             */
/*   Updated: 2019/03/18 09:39:06 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char    **ft_lst_to_arr(t_list *list)
{
    char    **result;
    int     count;
    int     index;

    count = ft_lstcount(list);
    result = (char **)malloc(sizeof(char *) * (count + 1));
    index = 0;
    while(list)
    {
        result[index] = (char *)list->content;
        list = list->next;
        index++;
    }
    result[index] = NULL;
    return (result);
}
