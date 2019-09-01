#include "pd_main.h"

pd_arr       pd_dast_init_arr(pd_type type, size_t len)
{
    pd_arr new_arr;

    new_arr.len = len;
    new_arr.type = type;
    new_arr.val = NULL;
    if (len > 0)
    {
        if (type == PD_T_ARR)
            new_arr.val = malloc(sizeof(pd_arr) * len);
        else if (type == PD_T_FLOAT)
            new_arr.val = malloc(sizeof(float) * len);
        else if (type == PD_T_SIZE_T)
            new_arr.val = malloc(sizeof(size_t) * len);
        else if (type == PD_T_STDIZ)
            new_arr.val = malloc(sizeof(pd_stdiz_data) * len);
        else if (type == PD_T_CHAR)
            new_arr.val = malloc(sizeof(char) * (len + 1));
        if (!new_arr.val)
            new_arr.len = 0;
    }
    if (type == PD_T_CHAR && len == 0)
    {
        new_arr.val = malloc(sizeof(char));
        ((char *)new_arr.val)[0] = 0;
    }
    return new_arr;
}

pd_arr   pd_dast_new_s_arr(pd_type type, size_t len, void* val)
{
    pd_arr new_arr;

    new_arr.len = len;
    new_arr.type = type;
    new_arr.val = NULL;
    if (len > 0)
    {
        if (type == PD_T_ARR)
        {
            pd_arr *new_val = malloc(sizeof(pd_arr) * len);
            if (new_val)
            {
                for (size_t i = 0; i < len; i++)
                    new_val[i] = ((pd_arr*)val)[i];
                new_arr.val = (void*)new_val;
            }
        }
        else if (type == PD_T_FLOAT)
        {
            float *new_val = malloc(sizeof(float) * len);
            if (new_val)
            {
                for (size_t i = 0; i < len; i++)
                    new_val[i] = ((float*)val)[i];
                new_arr.val = (void*)new_val;
            }
        }
        else if (type == PD_T_SIZE_T)
        {
            size_t *new_val = malloc(sizeof(size_t) * len);
            if (new_val)
            {
                for (size_t i = 0; i < len; i++)
                    new_val[i] = ((size_t*)val)[i];
                new_arr.val = (void*)new_val;
            }
        }
        else if (type == PD_T_STDIZ)
        {
            pd_ohe_trees *new_val = malloc(sizeof(pd_ohe_trees) * len);
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

pd_arr   pd_dast_new_arr(pd_type type, size_t len, void* val)
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

void    pd_dast_free_arr(pd_arr arr, int depth)
{
    if (arr.type == PD_T_ARR && (depth > 0 || depth == -1))
    {
        for (size_t i = 0; i < arr.len; i++)
            pd_dast_free_arr(((pd_arr*)arr.val)[i], depth == -1 ? -1 : depth -1);
    }
    pd_dast_free((void**)&arr.val);
}