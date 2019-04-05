#include "line_edit.h"

void        deleteline(t_tc *list, t_tcline *line)
{
    int x;
    int y;
    //int dx;

    if (line->next == NULL && line->prev == NULL)
        return movecursor(list, list->x, list->y);
    //else if(!(line->len % list->sw == 0 && line->len))
        //return movecursor(list, list->x, list->y);
    x = list->x;
    y = list->y;
    movecursor(list, list->x, list->y);
    movecursor(list, list->x - line->cursor % list->sw, list->y - line->cursor / list->sw);
    movecursor(list, 0, list->y + line->len / list->sw);
    line = line->next;
    while(line)
    {
        movecursor(list, 0, list->y + 1);
        tputs(tgetstr("cd", NULL), 1, ft_putcharc);
        ft_putstr(line->line);
        movecursor(list, list->x + line->len % list->sw, list->y + line->len / list->sw);
        line = line->next;
    }
    movecursor(list, x, y);
}

char        *migratelines(t_tcline *line)
{
    char *string;
    t_tcline *hline;
    int i;

    while(line)
    {
        hline = line;
        line = line->prev;
    }
    string = NULL;
    while(hline)
    {
        i = 0;
        while(hline->line[i])
            string = joinchar(&string, hline->line[i++], 0, 0);
        string = joinchar(&string, '\n', 0, 0);
        hline = hline->next;
    }
    return (string);
}

void    gotoend(t_tc *list, t_tcline *line)
{
    movecursor(list, list->x - line->cursor % list->sw, list->y - line->cursor / list->sw);
    while(line)
    {
        movecursor(list, 0, list->y + line->len / list->sw + 1);
        line = line->next;
    }
}