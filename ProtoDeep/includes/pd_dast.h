#ifndef PD_DAST_H
# define PD_DAST_H

// Lib

// Macro
# define PD_PRINT_SPACE		        "    "
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

# define pd_malloc(x)               pd_dast_malloc(x)
# define pd_free(x)                 pd_free_ctr((void**)&(x))
# define PD_PROT_MALLOC(x)          if (!(x)) {return NULL;}
# define PD_PROT_ARR_TYPE(x, y)     if (x != y) {return NULL;}

# define pd_error(...)              (fprintf(stderr, "%s%s%s[ERROR]%s %s%s: ", PD_COLOR_B, PD_COLOR_U, PD_COLOR_ERR_1, PD_COLOR_N, PD_COLOR_ERR_2, __func__), \
                                    fprintf(stderr, __VA_ARGS__), \
                                    fprintf(stderr, "%s\n", PD_COLOR_N), \
                                    exit(1))

# define pd_error_no_exit(...)      (fprintf(stderr, "%s%s%s[ERROR]%s %s%s: ", PD_COLOR_B, PD_COLOR_U, PD_COLOR_ERR_1, PD_COLOR_N, PD_COLOR_ERR_2, __func__), \
                                    fprintf(stderr, __VA_ARGS__), \
                                    fprintf(stderr, "%s\n", PD_COLOR_N))

# define pd_time(...)               (printf("%s%s%s[TIME]%s %s%lf sec: ", PD_COLOR_B, PD_COLOR_U, PD_COLOR_TIME_1, PD_COLOR_N, PD_COLOR_TIME_2, pd_dast_update_time()), \
                                    printf(__VA_ARGS__), \
                                    printf("%s\n", PD_COLOR_N))

# define pd_count                   register size_t

// Structures
typedef enum {false,true} bool;

// Prototypes
void	                            pd_free_ctr(void **ap);
double                              pd_dast_update_time(void);
void                                *pd_dast_malloc(size_t len);

extern char                         *pd_color_t[];

#endif