#include "line_edit.h"

void    deletchar(t_tc *list, t_tcline *line, char *buffer)
{
    if (line->cursor <= 0)
        return;
    line->len--;
    left(list, line);
    if (line->cursor < line->len)
        line->line = joinchar(&line->line, buffer[0], line->cursor, 3);
    else
        line->line = joinchar(&line->line, buffer[0], line->cursor, 2);
    tputs(tgetstr("cd", NULL), 1, ft_putcharc);
    ft_putstr(line->line + line->cursor);
    //movecursor(list, list->x, list->y);
    deleteline(list, line);
}

void    putlines(t_tc *list, t_tcline **pline)
{
    t_tcline *line;

    line = *pline;
    while (line)
    {
        ft_putstr(line->line);
        list->x += line->len % list->sw;
        list->y += line->len / list->sw;
        (list->y + 1 > list->sh) ? list->y = list->sh - 1: 0;
        if (line->next)
            movecursor(list, 0, list->y + 1);
        else
            line->cursor = line->len;
        *pline = line;
        line = line->next;
    } 
}

void prevline(t_tc *list, t_tcline **line)
{
    if (!(*line)->prev)
        return ;
    movecursor(list, list->x - (*line)->cursor % list->sw, list->y - (*line)->cursor / list->sw - 1);
    (*line)->cursor = 0;
    *line = (*line)->prev;
    movecursor(list, list->x, list->y - (*line)->len / list->sw);
}

void nextline(t_tc *list, t_tcline **line)
{
    if (!(*line)->next)
        return ;
    movecursor(list, list->x - (*line)->cursor % list->sw, list->y - (*line)->cursor / list->sw);
    (*line)->cursor = 0;
    movecursor(list, list->x, list->y + (*line)->len / list->sw + 1);
    *line = (*line)->next;
}

void fixlines(t_tc *list, t_tcline *line)
{
    int x;
    int y;
    int dx;

    if (line->next == NULL)
        return movecursor(list, list->x, list->y);
    else if(!(line->len % list->sw == 0 && line->len))
        return movecursor(list, list->x, list->y);
    x = list->x;
    y = list->y;
    movecursor(list, list->x, list->y);
    movecursor(list, list->x - line->cursor % list->sw, list->y - line->cursor / list->sw);
    movecursor(list, 0, list->y + line->len / list->sw);
    tputs(tgetstr("ce", NULL), 1, ft_putcharc);
    line = line->next;
    while(line)
    {
        movecursor(list, 0, list->y + 1);
        tputs(tgetstr("cd", NULL), 1, ft_putcharc);
        ft_putstr(line->line);
        dx = list->y + line->len / list->sw;
        movecursor(list, list->x + line->len % list->sw, (dx + 1 > list->sh) ? dx - 1 : dx);
        line = line->next;
    }
    movecursor(list, x, (dx + 1 > list->sh) ? y - 1 : y);
}