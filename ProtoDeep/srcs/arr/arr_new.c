#include "pd_main.h"

pd_arr   pd_arr_new_s(pd_type type, size_t len, void* val)
{
    pd_arr new_arr;

    new_arr.len = len;
    new_arr.type = type;
    new_arr.val = NULL;
    if (len > 0)
    {
        if (type == PD_T_ARR)
        {
            pd_arr *new_val = pd_malloc(sizeof(pd_arr) * len);
            if (new_val)
            {
                for (size_t i = 0; i < len; i++)
                    new_val[i] = ((pd_arr*)val)[i];
                new_arr.val = (void*)new_val;
            }
        }
        else if (type == PD_T_FLOAT)
        {
            float *new_val = pd_malloc(sizeof(float) * len);
            if (new_val)
            {
                for (size_t i = 0; i < len; i++)
                    new_val[i] = ((float*)val)[i];
                new_arr.val = (void*)new_val;
            }
        }
        else if (type == PD_T_SIZE_T)
        {
            size_t *new_val = pd_malloc(sizeof(size_t) * len);
            if (new_val)
            {
                for (size_t i = 0; i < len; i++)
                    new_val[i] = ((size_t*)val)[i];
                new_arr.val = (void*)new_val;
            }
        }
        else if (type == PD_T_STDIZ)
        {
            pd_ohe_trees *new_val = pd_malloc(sizeof(pd_ohe_trees) * len);
            if (new_val)
            {
                for (size_t i = 0; i < len; i++)
                    new_val[i] = ((pd_ohe_trees*)val)[i];
                new_arr.val = (void*)new_val;
            }
        }
        else if (type == PD_T_CHAR)
        {
            new_arr.len = pd_str_clen((char*)val);
            char *new_val = pd_malloc(sizeof(char) * (new_arr.len + 1));
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

pd_arr   pd_arr_new(pd_type type, size_t len, void* val)
{
    pd_arr new_arr;

    new_arr.type = type;
    if (len == 0 || !val)
    {
        new_arr.len = 0;
        new_arr.val = NULL;
    }
    else
    {
        new_arr.len = type == PD_T_CHAR ? pd_str_clen((char*)val) : len;
        new_arr.val = val;
    }
    return new_arr;
}