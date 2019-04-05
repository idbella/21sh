#include "line_edit.h"

void    history_up(t_tc *list, t_tcline *line, t_list *history)
{
    int i;

    i = 0;
    while(history)
    {
        if (i++ == list->history)
        {
            movecursor(list, list->x - line->cursor % list->sw, list->y - line->cursor / list->sw);
            tputs(tgetstr("cd", NULL), 1, ft_putcharc);
            ft_putstr((char *)history->content);
            line->line = ft_strdup((char *)history->content);
            line->len = ft_strlen(line->line);
            line->cursor = line->len;
            movecursor(list, list->x + line->len % list->sw, list->y + line->len / list->sw);
            break;
        }
        history = history->next;
    }
    list->history++;
}

void    history_down(t_tc *list, t_tcline *line, t_list *history)
{
    int i;

    if (list->history <= 0)
        return;
    i = 0;
    while(history)
    {
        if (i++ == list->history)
        {
            movecursor(list, list->x - line->cursor % list->sw, list->y - line->cursor / list->sw);
            tputs(tgetstr("cd", NULL), 1, ft_putcharc);
            ft_putstr((char *)history->content);
            line->line = ft_strdup((char *)history->content);
            line->len = ft_strlen(line->line);
            line->cursor = line->len;
            movecursor(list, list->x + line->len % list->sw, list->y + line->len / list->sw);
            break;
        }
        history = history->next;
    }
    list->history--;
}