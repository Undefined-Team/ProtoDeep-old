#ifndef PD_DAST_H
# define PD_DAST_H

// Lib

// Macro
# define PD_COLOR_N                 "\x1b[0m"
# define PD_COLOR_U                 "\x1b[4m"
# define PD_COLOR_B                 "\x1b[1m"
# define PD_COLOR_ERR_1             "\x1b[38;2;209;0;0m"
# define PD_COLOR_ERR_2             "\x1b[38;2;248;51;60m"
# define PD_COLOR_TIME_1            "\x1b[33m"
# define PD_COLOR_TIME_2            "\x1b[93m"
# define PD_COLOR_NBR               5
# define PD_COLOR_1                 "\x1b[38;2;68;175;105m"
# define PD_COLOR_2                 "\x1b[38;2;248;51;60m"
# define PD_COLOR_3                 "\x1b[38;2;43;158;179m"
# define PD_COLOR_4                 "\x1b[38;2;255;127;17m"
# define PD_COLOR_5                 "\x1b[38;2;255;1;251m"
// v = depth, w = arr, x = type, y = len, z = val
# define pd_arrInit(x, y)           pd_dast_init_arr(x, y)
# define pd_arrNew(x, y, z)         pd_dast_new_arr(x, y, z)
# define pd_arrSNew(x, y, z)        pd_dast_new_s_arr(x, y, z)
# define pd_arrFree(w)              pd_dast_free_arr(w, 0)
# define pd_arrRFree(w, v)          pd_dast_free_arr(w, v)

# define pd_strNew(z)               pd_arrNew(PD_T_CHAR, 1, z)
# define pd_strSNew(z)              pd_arrSNew(PD_T_CHAR, 1, z)
# define pd_strFree(w)              pd_arrRFree(w, 1)

# define pd_char_a                  pd_arr
# define pd_float_a                 pd_arr
# define pd_size_t_a                pd_arr
# define pd_str_a                   pd_arr
# define pd_stdiz_a                 pd_arr

# define PD_T_STR                   PD_T_ARR

# define PD_PROT_MALLOC(x)          if (!(x)) {return NULL;}
# define pd_malloc(x)               (x > 0 ? malloc(x) : NULL)
# define PD_PROT_ARR_TYPE(x, y)     if (x != y) {return pd_arrNew(y, 0, NULL);}

# define pd_error(...)              (fprintf(stderr, "%s%s%s[ERROR]%s %s%s: ", PD_COLOR_B, PD_COLOR_U, PD_COLOR_ERR_1, PD_COLOR_N, PD_COLOR_ERR_2, __func__), \
                                    fprintf(stderr, __VA_ARGS__), \
                                    fprintf(stderr, "%s\n", PD_COLOR_N), \
                                    exit(1))

# define pd_time(...)               (printf("%s%s%s[TIME]%s %s%lf sec: ", PD_COLOR_B, PD_COLOR_U, PD_COLOR_TIME_1, PD_COLOR_N, PD_COLOR_TIME_2, pd_dast_update_time()), \
                                    printf(__VA_ARGS__), \
                                    printf("%s\n", PD_COLOR_N))

// Structures
typedef enum {false,true} bool;
typedef enum {PD_T_ARR, PD_T_FLOAT, PD_T_SIZE_T, PD_T_CHAR, PD_T_STDIZ} pd_type;

typedef struct                      pds_arr {
    void                            *val;
    size_t                          len;
    pd_type                         type;
}                                   pd_arr;

// Prototypes
pd_arr                              pd_dast_init_arr(pd_type type, size_t len);
pd_arr                              pd_dast_new_s_arr(pd_type type, size_t len, void* val);
pd_arr                              pd_dast_new_arr(pd_type type, size_t len, void* val);
void                                pd_dast_free_arr(pd_arr arr, int depth);

void	                            pd_dast_free(void **ap);

double                              pd_dast_update_time(void);

extern char                         *pd_color_t[];

#endif