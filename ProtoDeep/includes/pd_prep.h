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
t_farr  prep_minmax_scal(t_farr x);
t_farr  prep_stdiz(t_farr x, t_prep_data pdata);
t_farr  prep_stdiz_init(t_farr x, t_prep_data *pdata);

#endif