#ifndef PD_PREP_H
# define PD_PREP_H

// Lib

// Macro

// Structures
typedef struct  s_prep_data {
    float       mean;
    float       std_dev;
}               t_prep_data;

// Prototypes
float   *prep_minmax_scal(float *x, size_t len);
float   *prep_stdiz(float *x, size_t len, t_prep_data pdata);
float   *prep_stdiz_init(float *x, size_t len, t_prep_data *pdata);

#endif