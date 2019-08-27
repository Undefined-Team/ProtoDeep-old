#include "pd_main.h"
# define BUF_SIZE 1000

t_arr  read_line(int fd, t_arr str)
{
    t_arr  buffer;
    int     ret;

    buffer = str_fill(0, 65);
    while ((ret = read(fd, ((char *)buffer.val), 64)) > 0)
    {
        ((char *)buffer.val)[ret] = 0;
        buffer.len = ret;
        str = str_join(str, buffer);
    }
    str.len = str_len(str);
    return (str);
}

int     csv_get_line(int fd, t_arr *line)
{
    static t_arr   str;
    int             i;

    if (!((char *)str.val))
        str = str_fill(0, 65);
    if (((char *)str.val)[0])
        *line = str_dup(str, str.len);
    str = read_line(fd, str);
    if (((char *)str.val)[0])
    {
        i = 0;
        while (((char *)str.val)[i] != '\n' && ((char *)str.val)[i])
            i++;
        if (!i)
            *line = arrInit(T_CHAR, 0);
        else
        {
            *line = str_sub(str, 0, i);
            line->len = i;
            str = arrInit(T_CHAR, str.len - i);
            str = str_sub(str, i + 1, str.len);
            str.len -= i;
        }
        return (1);
    }
    else
        *line = arrInit(T_CHAR, 0);
    return (0);
}

t_csv_col   *csv_read(char *file_name, int header)
{
    int         fd = open(file_name, O_RDONLY);
    t_arr       *line;
    t_arr       tokens;
    t_csv_col   *array = NULL;

    if (header)
        header = 0;
    line = (t_arr *)malloc(sizeof(t_arr));
    *line = arrInit(T_CHAR, 0);
    ((char *)line->val)[0] = 0;
    while (csv_get_line(fd, line))
    {
        tokens = str_split(*line, ',');
    }
    if (tokens.val)
        tokens.val = NULL;
    return (array);
}