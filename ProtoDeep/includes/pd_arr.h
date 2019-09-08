#ifndef PD_ARR_H
# define PD_ARR_H

// Macro
// v = depth, w = arr, x = type, y = len, z = val
# define pd_arr_free(w)             pd_arr_free_r(w, 0)
# define pd_str_new(z)              pd_arr_new(PD_T_CHAR, 1, z)
# define pd_str_new_s(z)            pd_arr_new_s(PD_T_CHAR, 1, z)
# define pd_str_free(w)             pd_arr_free_r(w, 1)
# define pd_arr_print(w)            pd_arr_print_ctr(w, 0)

# define pd_arr_float(x, ...)       pd_arr_value(x, PD_T_FLOAT, __VA_ARGS__)
# define pd_arr_size_t(x, ...)      pd_arr_value(x, PD_T_SIZE_T, __VA_ARGS__)
# define pd_arr_char(x, ...)        pd_arr_value(x, PD_T_CHAR, __VA_ARGS__)

# define pd_char_a                  pd_arr
# define pd_float_a                 pd_arr
# define pd_size_t_a                pd_arr
# define pd_str_a                   pd_arr
# define pd_stdiz_a                 pd_arr

# define PD_T_STR                   PD_T_ARR

// Structures
typedef enum {PD_T_ARR, PD_T_FLOAT, PD_T_SIZE_T, PD_T_CHAR, PD_T_STDIZ} pd_type;

typedef struct                      pds_arr {
    void                            *val;
    size_t                          len;
    pd_type                         type;
}                                   pd_arr;

// Prototypes
pd_arr                              *pd_arr_init(pd_type type, size_t len);
pd_arr                              *pd_arr_init_z(pd_type type, size_t len);
pd_arr                              *pd_arr_new_s(pd_type type, size_t len, void* val);
pd_arr                              *pd_arr_new(pd_type type, size_t len, void* val);
void                                pd_arr_free_r(pd_arr *arr, int depth);
void                                pd_arr_print_ctr(pd_arr *array, size_t space);
pd_size_t_a                         *pd_arr_shape(size_t len, ...);
pd_arr                              *pd_arr_concat_shape(pd_type type, pd_arr *a, pd_arr *b);
pd_char_a                           *pd_arr_get_shape(pd_arr *shape);
pd_arr                              *pd_arr_create(pd_size_t_a *arr_shape, pd_type type, ...);
pd_arr                              *pd_arr_copy(pd_arr *array);

#endif
