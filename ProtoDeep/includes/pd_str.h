#ifndef PD_STR_H
# define PD_STR_H

// Lib

// Macro

// Structures

// Prototypes
t_arr   str_join(t_arr head, t_arr tail);
t_arr   str_fjoin(t_arr head, t_arr tail);
size_t  str_clen(char* str);
size_t  str_len(t_arr str);
t_arr   str_dup(t_arr str, size_t len);
t_carr  str_sub(t_carr str, size_t start, size_t length);
t_starr str_split(t_carr str, char sep);
t_carr  str_whitespace(t_carr str);
t_carr  str_fill(char c, size_t len);
//t_carr  str_add_char(t_carr str, char c);
//t_carr  str_char_to_str(char c);
t_str   str_char_to_str(char c);
int     str_chr(t_carr str, char c);

#endif