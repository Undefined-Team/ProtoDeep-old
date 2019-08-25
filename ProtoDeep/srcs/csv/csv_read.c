#include "pd_main.h"
# define BUF_SIZE 1000

char    *read_line(int fd, char *str)
{
    char    buffer[65];
    int     ret;

    while ((ret = read(fd, buffer, 64)) > 0)
    {
        buffer[ret] = 0;
        str = str_join(str, buffer);
    }
    return (str);
}

int     csv_get_line(int fd, char **line)
{
    static char *str;
    int         i;

    if (!str)
        str = (char *)malloc(65);
    if (str[0])
        *line = str_dup(str);
    str = read_line(fd, str);
    if (str[0])
    {
        i = 0;
        while (str[i] != '\n' && str[i])
            i++;
        if (!i)
            *line = str_dup("");
        else
        {
            *line = str_sub(str, 0, i);
            str = &str[i + 1];
        }
        return (1);
    }
    else
        *line = str_dup("");
    return (0);
}

t_csv_col   csv_read(char *file_name, int header)
{
    int         fd = open(file_name, O_RDONLY);
    char        *line = str_dup("");
    char        **tokens = NULL;
    t_csv_col   *array;

    while (csv_get_line(fd, &line))
    {
        tokens = str_split(line, ',');
    }
    if (tokens)
        tokens = NULL;
}