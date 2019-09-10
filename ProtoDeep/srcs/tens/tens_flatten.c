#include "pd_main.h"

typedef struct      pds_s_flatten {
    size_t          begin;
    size_t          end;
    float           *t_flat_val;
    float           *t_tensor_val;
}                   pd_s_flatten;

void        *pd_tens_set_flat_val(void *p_data)
{
    pd_s_flatten    st = *(pd_s_flatten *)p_data;
    size_t          begin = st.begin;
    size_t          end = st.end;
    float           *t_flat_val = st.t_flat_val;
    float           *t_tensor_val = st.t_tensor_val;

    for (size_t i = begin; i < end; i++)
        t_flat_val[i] = t_tensor_val[i];
    pthread_exit(NULL);
}

pd_tensor   *pd_tens_flatten(pd_tensor *tensor)
{
    pd_tensor   *flat;
    float       *t_tensor_val;
    pd_size_t_a *len;

    len = pd_arr_shape(1, pd_tens_nb_values(tensor));
    flat = pd_tens_init_new_new(len);
    t_tensor_val = pd_tens_get_first_val(tensor);
    float *t_flat_val = (float *)flat->val;
    size_t flat_len = flat->len;
    pd_tens_print(flat);
    if (flat_len > 32000)
    {
        pd_s_flatten s_flatten =
        {
            .begin = 0,
            .end = flat_len / 2,
            .t_flat_val = t_flat_val,
            .t_tensor_val = t_tensor_val,
        };
        pd_s_flatten s_flatten2 =
        {
            .begin = flat_len / 2 + 1,
            .end = flat_len,
            .t_flat_val = t_flat_val,
            .t_tensor_val = t_tensor_val,
        };
        pthread_t thread[2];
        pthread_create(&thread[0], NULL, pd_tens_set_flat_val, &s_flatten);
        pthread_create(&thread[1], NULL, pd_tens_set_flat_val, &s_flatten2);
        for (size_t i = 0; i < 2; i++) pthread_join(thread[i], NULL);
    }
    else
        for (size_t i = 0; i < flat_len; i++)
            t_flat_val[i] = t_tensor_val[i];
    return (flat);
}