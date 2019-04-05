#include "line_edit.h"

int isnespace(t_tc *list, t_tcline *line)
{
    int dx;
    int x;
    int hx;

    dx = line->len - line->cursor;
    hx = (list->sh) * (list->sw - 1);
    x = (dx / (list->sw - 1) + list->y) * (list->sw - 1) + ((dx % (list->sw - 1)) + list->x);
    return (x >= hx);
}

void  previewword(t_tc *list, t_tcline *line)
{
    int dx;

    if (line->cursor == 0)
        return ;
    dx = line->cursor;
    (dx == line->len) ? dx--: 0;
    (line->line[dx - 1] == ' ') ? dx-- : 0;
    while(line->line[dx] && line->line + dx != line->line)
        if (line->line[dx] == ' ')
            dx--;
        else
            break;
    while(line->line[dx] && line->line + dx != line->line)
        if (!(line->line[dx] == ' '))
            dx--;
        else
            break;
    (dx) ? dx++ : 0;
    movecursor(list, list->x - (line->cursor % list->sw), list->y - (line->cursor / list->sw));
    movecursor(list, list->x + (dx % list->sw), list->y + (dx / list->sw));
    line->cursor = dx;
}

void nextword(t_tc *list, t_tcline *line)
{
    int dx;

    dx = line->cursor;
    while(line->line[dx])
        if (!(line->line[dx] == ' '))
            dx++;
        else
            break;
    while(line->line[dx])
        if (line->line[dx] == ' ')
            dx++;
        else
            break;
    movecursor(list, list->x - (line->cursor % list->sw), list->y - (line->cursor / list->sw));
    movecursor(list, list->x + (dx % list->sw), list->y + (dx / list->sw));
    line->cursor = dx;
}

void gobegin(t_tc *list, t_tcline *line)
{
    int dy;

    dy = line->cursor / list->sw;
    line->cursor = 0;
    movecursor(list, 0, list->y - dy);
}

void goend(t_tc *list, t_tcline *line)
{
    int dx;
    int dy;

    dy = (line->len - line->cursor) / list->sw;
    dx = (line->len - line->cursor) % list->sw;
    line->cursor = line->len;
    movecursor(list, list->x + dx, list->y + dy);
}