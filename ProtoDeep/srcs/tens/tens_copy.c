#include "pd_main.h"

/*pd_tensor *pd_tens_copy(pd_tensor *tensor)
{
    pd_tensor *new_tensor;

    new_tensor = pd_tens_new(tensor->rank, tensor->len, NULL, pd_arr_new(PD_T_SIZE_T, 0, NULL));
    size_t new_tensor_len = new_tensor->len;
    if (new_tensor->rank == 1)
    {
        float *a_new_tensor = pd_malloc(sizeof(float) * new_tensor_len);
        new_tensor->val = a_new_tensor;
        float *a_tensor = (float*)tensor->val;
        for (size_t i = 0; i < new_tensor_len; i++)
            a_new_tensor[i] = a_tensor[i];
    }
    else
    {
        pd_tensor **a_new_tensor = pd_malloc(sizeof(pd_tensor*) * new_tensor_len);
        new_tensor->val = a_new_tensor;
        pd_tensor **a_tensor = (pd_tensor**)tensor->val;
        for (size_t i = 0; i < new_tensor_len; i++)
            a_new_tensor[i] = pd_tens_copy(a_tensor[i]);
    }
    new_tensor->shape = pd_tens_get_shape(new_tensor);
    return new_tensor;
}*/

typedef struct  pds_tens_copy_data {
    pd_tensor   *dst;
    pd_tensor   *src;
    size_t      i;
    size_t      len;
}               pd_tens_copy_data;

static void     pd_tens_copy_ctr(pd_tensor *dst, pd_tensor *src)
{
    size_t len = src->len;

    if (src->rank > 1)
    {
        pd_tensor **a_dst_val = (pd_tensor**)dst->val;
        pd_tensor **a_src_val = (pd_tensor**)src->val;
        for (size_t i = 0; i < len; i++) pd_tens_copy_ctr(a_dst_val[i], a_src_val[i]);
    }
    else
    {
        float *a_dst_val = (float*)dst->val;
        float *a_src_val = (float*)src->val;
        for (size_t i = 0; i < len; i++) a_dst_val[i] = a_src_val[i];
    }
}

// static void     *pd_tens_copy_ctr_thread(void * p_data)
// {
//     pd_tens_copy_data st    = *(pd_tens_copy_data*)p_data;
//     pd_tensor *dst          = st.dst;
//     pd_tensor *src          = st.src;
//     size_t     i            = st.i;
//     size_t     len          = st.len;

//     if (src->rank > 1)
//     {
//         pd_tensor **a_dst_val = (pd_tensor**)dst->val;
//         pd_tensor **a_src_val = (pd_tensor**)src->val;
//         for (; i < len; i++) pd_tens_copy_ctr(a_dst_val[i], a_src_val[i]);
//     }
//     else
//     {
//         float *a_dst_val = (float*)dst->val;
//         float *a_src_val = (float*)src->val;
//         for (; i < len; i++) a_dst_val[i] = a_src_val[i];
//     }
//     pthread_exit(NULL);
// }

pd_tensor       *pd_tens_copy_new(pd_tensor *tensor)
{
    // pd_tensor *new_tensor = pd_tens_init_new_new(pd_arr_copy(tensor->shape));
    // size_t len = tensor->len / 2;
    // pd_tens_copy_data s_tcd_a =
    // {
    //     .dst = new_tensor,
    //     .src = tensor,
    //     .i = 0,
    //     .len = len,
    // };
    // pd_tens_copy_data s_tcd_b =
    // {
    //     .dst = new_tensor,
    //     .src = tensor,
    //     .i = len,
    //     .len = tensor->len,
    // };
    // pthread_t thread[2];
    // pthread_create(&thread[0], NULL, pd_tens_copy_ctr_thread, &s_tcd_a);
    // pthread_create(&thread[1], NULL, pd_tens_copy_ctr_thread, &s_tcd_b);
    // for(size_t i = 0; i < 2; i++) pthread_join(thread[i], NULL);
    // return new_tensor;

    pd_tensor *new_tensor = pd_tens_init(pd_arr_copy(tensor->shape));
    pd_tens_copy_ctr(new_tensor, tensor);
    return new_tensor;
}