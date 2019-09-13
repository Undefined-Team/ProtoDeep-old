#include "pd_main.h"

pd_tensor *pd_tens_init_val_new(pd_size_t_a *new_shape, float val)
{
    size_t nbr_float;
    size_t nbr_tensor;
    size_t nbr_p_tensor;
    pd_count shape_len = new_shape->len;
    if (shape_len == 0) pd_error("Rank must be greater than 0 (Bad shape <-> length ?)");
    size_t *shape = (size_t*)new_shape->val;
    pd_free(new_shape);

    size_t *shape_div = pd_get_shape_div(shape, shape_len, &nbr_float, &nbr_p_tensor, &nbr_tensor);

    size_t i_mem_float          = sizeof(float) * nbr_float;
    size_t i_mem_p_tensor       = sizeof(pd_tensor*) * nbr_p_tensor;
    size_t i_mem_tensor         = sizeof(pd_tensor) * nbr_tensor;
    size_t i_new_shapes         = sizeof(pd_arr) * shape_len;
    void *mem_total             = pd_malloc(i_mem_float + i_mem_p_tensor + i_mem_tensor + i_new_shapes);

    pd_tensor   *mem_tensor     = mem_total;
    mem_total                   += i_mem_tensor;
    pd_tensor   **mem_p_tensor  = mem_total;
    mem_total                   += i_mem_p_tensor;
    float       *mem_float      = mem_total;
    mem_total                   += i_mem_float;
    pd_arr      *new_shapes     = mem_total; 
    printf("%zd %zd %zd %zd\n", i_mem_tensor, i_mem_p_tensor, i_mem_float, i_new_shapes);
    printf("%zd %zd %zd %zd\n", nbr_tensor, nbr_p_tensor, nbr_float, shape_len);
    printf("%zd\n", i_mem_float + i_mem_p_tensor + i_mem_tensor + i_new_shapes);
    // float       *mem_float      = pd_malloc(sizeof(float) * nbr_float);
    // pd_tensor   **mem_p_tensor  = pd_malloc(sizeof(pd_tensor*) * nbr_p_tensor);
    // pd_tensor   *mem_tensor     = pd_malloc(sizeof(pd_tensor) * nbr_tensor);
    // pd_arr      *new_shapes     = pd_malloc(sizeof(pd_arr) * shape_len);

    size_t len = nbr_float;
    float *val_arr = mem_float;
    while (len-- > 0) *val_arr++ = val;

    pd_tensor *mem_tensor_2 = mem_tensor + 1;
    pd_tensor **mem_p_tensor_2 = mem_p_tensor;
    len = nbr_p_tensor;
    while (len-- > 0) *mem_p_tensor_2++ = mem_tensor_2++;


    pd_tensor *begin = mem_tensor;
    // size_t shape_len_begin = shape_len - 1; // PEUT ETRE ON PEUT NE PLUS UTILISER SHAPE LEN
    size_t *shape_div_tmp = shape_div;
    size_t step;
    size_t rank = shape_len;
    // --shape_len;
    // size_t *shape_tmp = shape;

    pd_count i = 0;
    pd_count j = 0;
    while (i < shape_len)
    {
        pd_arr_val(new_shapes, PD_T_SIZE_T, rank, shape);
        step = *shape++;
        while (j < *shape_div_tmp)
        {
            mem_tensor->val = mem_p_tensor;
            mem_tensor->len = step;
            mem_tensor->rank = rank;
            mem_tensor->shape = new_shapes;
            mem_p_tensor += step;
            ++mem_tensor; // PEUT ETRE PAS BESOIN DE CA NN PLUS
            ++j; // PEUT ETRE PAS BESOIN DE CA NN PLUS
        }
        ++new_shapes;
        ++shape_div_tmp;
        --rank;
        ++i; // PEUT ETRE PAS BESOIN DE CA NN PLUS
    }

    // pd_arr_val(new_shapes, PD_T_SIZE_T, 1, shape);
    // step = *shape;
    // while (j < *shape_div_tmp)
    // {
    //     mem_tensor->val = mem_float;
    //     mem_tensor->len = step;
    //     mem_tensor->rank = 1;
    //     mem_tensor->shape = new_shapes;
    //     mem_float += step;
    //     ++mem_tensor; // PEUT ETRE PAS BESOIN DE CA
    //     ++j;
    // }

    //-------------------
    // pd_tensor *begin = mem_tensor;
    // pd_tensor *mem_tensor_2 = mem_tensor + 1;
    // // size_t shape_len_begin = shape_len - 1; // PEUT ETRE ON PEUT NE PLUS UTILISER SHAPE LEN
    // size_t *shape_div_tmp = shape_div;
    // size_t step;
    // size_t rank = shape_len;
    // --shape_len;
    // // size_t *shape_tmp = shape;

    // pd_count i = 0;
    // pd_count j = 0;
    // pd_count k;
    // while (i < shape_len)
    // {
    //     pd_arr_val(new_shapes, PD_T_SIZE_T, rank, shape);
    //     step = *shape++;
    //     while (j < *shape_div_tmp)
    //     {
    //         mem_tensor->val = mem_p_tensor;
    //         mem_tensor->len = step;
    //         mem_tensor->rank = rank;
    //         mem_tensor->shape = new_shapes;
    //         for (k = 0; k < step; ++k)
    //             *mem_p_tensor++ = mem_tensor_2++;
    //         ++mem_tensor; // PEUT ETRE PAS BESOIN DE CA NN PLUS
    //         ++j; // PEUT ETRE PAS BESOIN DE CA NN PLUS
    //     }
    //     ++new_shapes;
    //     ++shape_div_tmp;
    //     --rank;
    //     ++i; // PEUT ETRE PAS BESOIN DE CA NN PLUS
    // }

    // pd_arr_val(new_shapes, PD_T_SIZE_T, 1, shape);
    // step = *shape;
    // while (j < *shape_div_tmp)
    // {
    //     mem_tensor->val = mem_float;
    //     mem_tensor->len = step;
    //     mem_tensor->rank = 1;
    //     mem_tensor->shape = new_shapes;
    //     for (k = 0; k < step; ++k)
    //         *mem_float++ = val;
    //     ++mem_tensor; // PEUT ETRE PAS BESOIN DE CA
    //     ++j;
    // }
    //-------------------

    pd_free(shape_div);
    return begin;
}