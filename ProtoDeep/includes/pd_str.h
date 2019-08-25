#ifndef PD_STR_H
# define PD_STR_H

// Lib

// Macro

// Structures

// Prototypes
t_carr  str_join(t_carr head, t_carr tail);
size_t  str_len(t_carr str);
t_carr  str_dup(t_carr str, size_t len);
t_carr  str_sub(t_carr str, size_t start, size_t length);
t_starr str_split(t_carr str, char sep);
t_carr  str_whitespace(t_carr str);
t_carr  str_fill(char c, size_t len);
int     str_chr(t_carr str, char c);

#endif