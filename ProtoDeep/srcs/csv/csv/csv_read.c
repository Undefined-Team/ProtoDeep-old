#include "pd_main.h"

pd_csv       pd_csv_init(pd_csv_col *cols, int header, size_t width, size_t height)
{
    pd_csv   csv;

    csv.begin = cols;
    csv.width = width;
    csv.height = height - header;
    return (csv);
}

pd_csv   pd_csv_read(char *file_name, char separator, int header)
{
    int             fd;
    pd_csv           csv;
    pd_csv_col       *cols = NULL;
    pd_tokens_list   *tokens_list = NULL;
    size_t          height = 0;
    size_t          width = 0;

    if (!file_name || ((fd = open(file_name, O_RDONLY)) < 0))
        return (pd_csv_init(NULL, 0, 0, 0));
    if (!(tokens_list = pd_csv_create_tokens_list(fd, separator, &height, &width)))
        return (pd_csv_init(NULL, 0, 0, 0));
    cols = pd_csv_create_cols(tokens_list, header, width, height);
    csv = pd_csv_init(cols, header, width, height);
    return (csv);
}