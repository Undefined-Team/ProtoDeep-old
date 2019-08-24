#include "pd_main.h"
# define BUF_SIZE 1000

char    *csv_get_line(char *buf)
{
    static char *line;

    if (line)
        line = NULL;
    printf("%s\n", buf);
    return (buf);
}

void    csv_parser(char *file_name)
{
    int     fd = open(file_name, O_RDONLY);
    char    *buf = malloc(BUF_SIZE + 1);

    if (fd)
    {
        while (read(fd, (void*)buf, BUF_SIZE))
            csv_get_line(buf);
    }
}