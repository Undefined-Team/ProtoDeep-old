#ifndef PD_PREP_H
# define PD_PREP_H

// Lib

// Macro

// Structures
typedef struct              pds_tbnode {
    char                    c;
    int                     word_index;
    struct pds_tbnode       *next;
    struct pds_tbnode       *f_begin;
    struct pds_tbnode       *f_last;
}                           pd_tbnode;

typedef struct              pds_ohe_trees {
    pd_char_a               base_name;
    pd_str_a                new_names; 
    pd_tbnode               *begin;
    struct pds_ohe_trees    *next;
}                           pd_ohe_trees;

typedef struct              pds_csv_conf {
    pd_str_a                delete_indexs;
    pd_str_a                ohe_indexs;
    pd_stdiz_a              std_data;
    pd_ohe_trees            *saved_trees;
}                           pd_csv_conf;

typedef struct              pds_stdiz_data {
    float                   mean;
    float                   std_dev;
    float                   min;
    float                   maxsmin;
}                           pd_stdiz_data;

typedef struct              pds_name_index {
    pd_char_a               name;
    size_t                  index;
    struct pds_name_index   *next;
}                           pd_name_index;

// Prototypes
pd_float_a                  pd_prep_minmax_scal(pd_float_a x);
pd_float_a                  pd_prep_stdiz(pd_float_a x, pd_stdiz_data pdata);
pd_float_a                  pd_prep_stdiz_init(pd_float_a x, pd_stdiz_data *pdata);
pd_stdiz_a                  pd_prep_strandardize_init(pd_csv csv);
void                        pd_prep_standardize(pd_csv csv, pd_stdiz_a std_data);

void                        pd_prep_free_ohe_tree(pd_ohe_trees *ohe_trees);
void                        pd_prep_add_line(pd_csv_col *begin_col, size_t col_index, size_t line_index);
pd_csv_col                  *pd_prep_add_col(pd_csv_col *laspd_col, size_t nbr_line, size_t max_line, pd_char_a name);
pd_ohe_trees                *pd_prep_ohe_init(pd_csv *csv, pd_str_a col_names);
void                        pd_prep_ohe(pd_csv *csv, pd_ohe_trees *tbegin);
void                        pd_prep_delete(pd_csv *csv, pd_str_a col_names);

pd_csv_conf                 pd_prep_inipd_conf(pd_str_a delete_indexs, pd_str_a ohe_indexs);
void                        pd_prep_free_conf(pd_csv_conf conf);
void                        pd_prep_prepare(pd_csv *csv, pd_csv_conf *conf);
void                        pd_prep_all_to_float(pd_csv csv);
int                         pd_prep_csv_split(pd_csv csv, pd_csv *train, pd_csv *test, float f_split);

pd_tbnode                   *pd_prep_new_tbnode(char c, int word_index);
void                        pd_prep_free_tbnode(pd_tbnode *begin);
pd_str_a                    pd_prep_name_sort(pd_csv csv, pd_str_a col_ni);

#endif
