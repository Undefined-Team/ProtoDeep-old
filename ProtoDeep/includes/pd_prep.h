#ifndef PD_PREP_H
# define PD_PREP_H

// Lib

// Macro

// Structures
typedef struct  s_prep_data {
    float       mean;
    float       std_dev;
    float       min;
    float       maxsmin;
}               t_prep_data;

// Prototypes
t_float_a   prep_minmax_scal(t_float_a x);
t_float_a   prep_stdiz(t_float_a x, t_prep_data pdata);
t_float_a   prep_stdiz_init(t_float_a x, t_prep_data *pdata);
void        prep_ohe(t_csv *csv, t_arr col_indexs);

#endif