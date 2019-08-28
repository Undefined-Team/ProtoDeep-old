#ifndef PD_DBUG_H
# define PD_DBUG_H

// Lib

// Macro
# define DBUG_PREC 3

// Structures
# define COLOR_N    "\x1b[0m"
# define COLOR_U    "\x1b[4m"
# define COLOR_1    "\x1b[38;2;68;175;105m"
# define COLOR_2    "\x1b[38;2;248;51;60m"
# define COLOR_3    "\x1b[38;2;43;158;179m"
# define COLOR_4    "\x1b[38;2;255;127;17m"
# define COLOR_5    "\x1b[38;2;255;1;251m"
# define COLOR_T     {COLOR_1, COLOR_2, COLOR_3, COLOR_4, COLOR_5}

// Prototypes
void    dbug_print_csv(t_csv csv);

#endif