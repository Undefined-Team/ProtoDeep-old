#ifndef PD_PREP_H
# define PD_PREP_H

// Lib

// Macro

// Structures
typedef struct      s_csv_conf {
    t_float_a       delete_indexs;
    t_float_a       ohe_indexs;
    t_stdiz_a       std_data;
}                   t_csv_conf;

typedef struct      s_stdiz_data {
    float           mean;
    float           std_dev;
    float           min;
    float           maxsmin;
}                   t_stdiz_data;

// Prototypes
t_float_a   prep_minmax_scal(t_float_a x);
t_float_a   prep_stdiz(t_float_a x, t_stdiz_data pdata);
t_float_a   prep_stdiz_init(t_float_a x, t_stdiz_data *pdata);
void        prep_standardize(t_csv *csv, t_csv_conf *conf);
void        prep_ohe(t_csv *csv, t_arr col_indexs);
void        prep_delete(t_csv *csv, t_size_t_a col_indexs);
void        prep_ohe_delete(t_csv *csv, t_size_t_a ohe_indexs, t_size_t_a del_indexs);
t_csv_conf  prep_init_conf(t_size_t_a delete_indexs, t_size_t_a ohe_indexs);
void        prep_prepare(t_csv *csv, t_csv_conf *conf);
void        prep_all_to_float(t_csv *csv);

#endif