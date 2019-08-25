#include "pd_main.h"
# define BUF_SIZE 1000

t_carr  read_line(int fd, t_carr str)
{
    t_carr  buffer;
    int     ret;

    buffer = str_fill(0, 65);
    while ((ret = read(fd, buffer.arr, 64)) > 0)
    {
        buffer.arr[ret] = 0;
        str = str_join(str, buffer);
    }
    str.len = str_len(str);
    return (str);
}

int     csv_get_line(int fd, t_carr *line)
{
    static t_carr   str;
    int             i;

    if (!str.arr)
        str = str_fill(0, 65);
    if (str.arr[0])
        *line = str_dup(str, str.len);
    str = read_line(fd, str);
    if (str.arr[0])
    {
        i = 0;
        while (str.arr[i] != '\n' && str.arr[i])
            i++;
        if (!i)
            *line = dast_new_carr("", 0);
        else
        {
            *line = str_sub(str, 0, i);
            str.arr = &(str.arr[i + 1]);
            str.len -= i;
        }
        return (1);
    }
    else
        *line = dast_new_carr("", 0);
    return (0);
}

t_csv_col   csv_read(char *file_name, int header)
{
    int         fd = open(file_name, O_RDONLY);
    t_carr      *line;
    t_starr     tokens;
    t_csv_col   array;

    if (header)
        header = 0;
    line = (t_carr *)malloc(sizeof(t_carr));
    *line = dast_new_carr("", 0);
    while (csv_get_line(fd, line))
    {
        tokens = str_split(*line, ',');
    }
    if (tokens.arr)
        tokens.arr = NULL;
    return (array);
}