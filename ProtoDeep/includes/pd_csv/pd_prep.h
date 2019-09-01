#ifndef PD_PREP_H
# define PD_PREP_H

// Lib

// Macro

// Structures
typedef struct              s_tbnode {
    char                    c;
    int                     word_index;
    struct s_tbnode         *next;
    struct s_tbnode         *f_begin;
    struct s_tbnode         *f_last;
}                           t_tbnode;

typedef struct              s_ohe_trees {
    t_char_a                base_name;
    t_str_a                 new_names; 
    t_tbnode                *begin;
    struct s_ohe_trees      *next;
}                           t_ohe_trees;

typedef struct              s_csv_conf {
    t_str_a                 delete_indexs;
    t_str_a                 ohe_indexs;
    t_stdiz_a               std_data;
    t_ohe_trees             *saved_trees;
}                           t_csv_conf;

typedef struct              s_stdiz_data {
    float                   mean;
    float                   std_dev;
    float                   min;
    float                   maxsmin;
}                           t_stdiz_data;

typedef struct              s_name_index {
    t_char_a                name;
    size_t                  index;
    struct s_name_index     *next;
}                           t_name_index;

// Prototypes
t_float_a                   prep_minmax_scal(t_float_a x);
t_float_a                   prep_stdiz(t_float_a x, t_stdiz_data pdata);
t_float_a                   prep_stdiz_init(t_float_a x, t_stdiz_data *pdata);
t_stdiz_a                   prep_strandardize_init(t_csv csv);
void                        prep_standardize(t_csv csv, t_stdiz_a std_data);

void                        prep_free_ohe_tree(t_ohe_trees *ohe_trees);
void                        prep_add_line(t_csv_col *begin_col, size_t col_index, size_t line_index);
t_csv_col                   *prep_add_col(t_csv_col *last_col, size_t nbr_line, size_t max_line, t_char_a name);
t_ohe_trees                 *prep_ohe_init(t_csv *csv, t_str_a col_names);
void                        prep_ohe(t_csv *csv, t_ohe_trees *tbegin);
void                        prep_delete(t_csv *csv, t_str_a col_names);

t_csv_conf                  prep_init_conf(t_str_a delete_indexs, t_str_a ohe_indexs);
void                        prep_free_conf(t_csv_conf conf);
void                        prep_prepare(t_csv *csv, t_csv_conf *conf);
void                        prep_all_to_float(t_csv csv);
int                         prep_csv_split(t_csv csv, t_csv *train, t_csv *test, float f_split);

t_tbnode                    *prep_new_tbnode(char c, int word_index);
void                        prep_free_tbnode(t_tbnode *begin);
t_str_a                     prep_name_sort(t_csv csv, t_str_a col_ni);

#endif
