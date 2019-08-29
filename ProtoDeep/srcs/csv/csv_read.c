#include "pd_main.h"
# define BUF_SIZE 1000

t_csv       *csv_init(t_csv_col *array, int header, size_t width, size_t height)
{
    t_csv   *csv;

    csv = (t_csv *)malloc(sizeof(t_csv));
    csv->begin = array;
    csv->width = width;
    csv->height = height - header;
    return (csv);
}

t_csv   *csv_read(char *file_name, int header)
{
    int             fd;
    t_csv           *csv = NULL;
    t_csv_col       *cols = NULL;
    t_tokens_list   *tokens_list = NULL;
    size_t          height = 0;
    size_t          width = 0;

    if (!file_name || ((fd = open(file_name, O_RDONLY)) < 0))
        return (NULL);
    if (!(tokens_list = csv_create_tokens_list(fd, &height, &width)))
        return (NULL);
    if (!(cols = create_cols(tokens_list, header, width, height)))
        return (NULL);
    if (!(csv = csv_init(cols, header, width, height)))
        return (NULL);
    return (csv);
}