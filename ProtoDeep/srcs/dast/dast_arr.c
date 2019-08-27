#include "pd_main.h"

t_arr       dast_init_arr(type type, size_t len)
{
    t_arr new_arr;

    new_arr.len = len;
    new_arr.type = type;
    new_arr.val = NULL;
    if (len > 0)
    {
        if (type == T_STR)
            new_arr.val = malloc(sizeof(t_arr) * len);
        else if (type == T_FLOAT)
            new_arr.val = malloc(sizeof(float) * len);
        else if (type == T_SIZE_T)
            new_arr.val = malloc(sizeof(size_t) * len);
        else if (type == T_CHAR)
            new_arr.val = malloc(sizeof(char) * (len + 1));
        if (!new_arr.val)
            new_arr.len = 0;
    }
    return new_arr;
}

t_arr   dast_new_s_arr(type type, size_t len, void* val)
{
    t_arr new_arr;

    new_arr.len = len;
    new_arr.type = type;
    new_arr.val = NULL;
    if (len > 0)
    {
        if (type == T_STR)
        {
            t_arr *new_val = malloc(sizeof(t_arr) * len);
            if (new_val)
            {
                for (size_t i = 0; i < len; i++)
                    new_val[i] = ((t_arr*)val)[i];
                new_arr.val = (void*)new_val;
            }
        }
        else if (type == T_FLOAT)
        {
            float *new_val = malloc(sizeof(float) * len);
            if (new_val)
            {
                for (size_t i = 0; i < len; i++)
                    new_val[i] = ((float*)val)[i];
                new_arr.val = (void*)new_val;
            }
        }
        else if (type == T_SIZE_T)
        {
            size_t *new_val = malloc(sizeof(size_t) * len);
            if (new_val)
            {
                for (size_t i = 0; i < len; i++)
                    new_val[i] = ((size_t*)val)[i];
                new_arr.val = (void*)new_val;
            }
        }
        else if (type == T_CHAR)
        {
            new_arr.len = str_clen((char*)val);
            char *new_val = malloc(sizeof(char) * (new_arr.len + 1));
            if (new_val)
            {
                for (size_t i = 0; i < new_arr.len; i++)
                    new_val[i] = ((char*)val)[i];
                new_val[new_arr.len] = '\0';
                new_arr.val = (void*)new_val;
            }
        }
    }
    if (!new_arr.val)
        new_arr.len = 0;
    return new_arr;
}

t_arr   dast_new_arr(type type, size_t len, void* val)
{
    t_arr new_arr;

    new_arr.type = type;
    if (len == 0 || !val)
    {
        new_arr.len = 0;
        new_arr.val = NULL;
    }
    else
    {
        new_arr.len = type == T_CHAR ? str_clen((char*)val) : len;
        new_arr.val = val;
    }
    return new_arr;
}