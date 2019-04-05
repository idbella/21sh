#include "line_edit.h"

char *joinchar(char **base, char extend, int index, int mode)
{
    char *result;
    char *tmp;
    int i;
    int j;

    tmp = *base;
    result = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + 2));
    i = 0;
    if (mode == 0)
    {
        if (tmp)
            while(tmp[i])
            {
                result[i] = tmp[i];
                i++;
            }
        result[i++] = extend;
    }
    else if (mode == 1)
    {
        j = 0;
        while(tmp[i] && i < index)
            result[j++] = tmp[i++];  
        result[j++] = extend;
        while(tmp[i])
            result[j++] = tmp[i++];
        i = j;
    }
    else if (mode == 2)
    {
        while(tmp[i] && tmp[i + 1])
        {
            result[i] = tmp[i];
            i++;
        }
    }
    else if (mode == 3)
    {
        j = 0;
        while(tmp[i] && i < index)
            result[j++] = tmp[i++];
        i++;
        while(tmp[i])
            result[j++] = tmp[i++];
        i = j;
    }
    result[i] = '\0';
    free(*base);
    return (result);
}

char   *read_setup(t_list *history)
{
    t_tc *list;
    t_tcline *tclines;

    list = init();
    if (!list)
        return (NULL);
    //tclines = setlines(content);
    //if (!tclines)
    //{
    tclines = (t_tcline *)malloc(sizeof(t_tcline));
    tclines->line = NULL;
    tclines->cursor = 0;
    tclines->len = 0;
    tclines->next = NULL;
    tclines->prev = NULL;
    //}
    //else
        //putlines(list, &tclines);
    read_key(list, tclines, history);
    tcsetattr(0, TCSANOW, &list->termi);
    return (migratelines(tclines));
}

int     ft_iskey(char *buffer, int key, int kkey, int kkkey)
{
    if (buffer[0] == key &&
        buffer[1] == kkey &&
        buffer[2] == kkkey)
        return (1);
    return (0);
}

void    ft_puttext(t_tc *list, t_tcline *line, char *buffer)
{
    if (line->cursor < line->len)
        line->line = joinchar(&line->line, buffer[0], line->cursor, 1);
    else
        line->line = joinchar(&line->line, buffer[0], line->cursor, 0);
    tputs(tgetstr("im", NULL), 1, ft_putcharc);
    tputs(tgetstr("ic", NULL), 1, ft_putcharc);
    write(1, buffer, 1);
    tputs(tgetstr("ei", NULL), 1, ft_putcharc);
    list->x++;
    line->cursor++;
    (line->len % list->sw == 0 && line->len && isnespace(list, line)) ? list->y-- : 0;
    line->len++;
    if (line->cursor % list->sw == 0 && line->cursor)
    {
        list->x = 0;
        list->y++;
    } 
    (line->cursor < line->len) ? ft_putstr(line->line + line->cursor) : 0;
    //(line->len % list->sw == 0 && line->len && line->next) ? 
    fixlines(list, line); 
    //movecursor(list, list->x, list->y);
}

void    read_key(t_tc *list, t_tcline *line, t_list *history)
{
    char buffer[4];

    ft_memset(buffer, 0, 4);
    while (read(0, &buffer, 3) > 0)
    {
        if (!ft_iskey(buffer, -61, -89, 0) && !ft_iskey(buffer, -30, -119, -91) && !ft_iskey(buffer, -30, -119, -92))
            clearselect(list, line);
        
        if (ft_iskey(buffer, 13, 0, 0))
            return gotoend(list, line);
        else if (ft_iskey(buffer, 27, 91, 67))
            right(list, line);
        else if (ft_iskey(buffer, 27, 91, 68))
            left(list, line);
        else if (ft_iskey(buffer, 27, 91, 65))
            history_up(list, line, history);
        else if (ft_iskey(buffer, 27, 91, 66))
            history_down(list, line, history);
        else if (ft_iskey(buffer, -62, -84, 0))
            nextword(list, line);
        else if (ft_iskey(buffer, -53, -102, 0))
            previewword(list, line);
        else if (ft_iskey(buffer, 27, 91, 72))
            gobegin(list, line);
        else if (ft_iskey(buffer, 27, 91, 70))
            goend(list, line);
        else if (ft_iskey(buffer, -30, -119, -91))
            selectext(list, line);
        else if (ft_iskey(buffer, -30, -119, -92))
            reverselectext(list, line);
        else if (ft_iskey(buffer, -61, -89, 0))
            copy(list, line, 0);
        else if (ft_iskey(buffer, -30, -120, -102))
            past(list, line);
        else if (ft_iskey(buffer, 127, 0, 0))
            deletchar(list, line, buffer);
        else if (ft_iskey(buffer, 113, 0, 0))
            prevline(list, &line);
        else if (ft_iskey(buffer, 97, 0, 0))
            nextline(list, &line);
        else
            ft_puttext(list, line, buffer);
        //printf("%d %d %d\n", buffer[0], buffer[1], buffer[2]);
        ft_memset(buffer, 0, 4);
    }
}