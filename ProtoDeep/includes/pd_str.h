#ifndef PD_STR_H
# define PD_STR_H

// Lib

// Macro

// Structures

// Prototypes
t_arr       str_join(t_arr head, t_arr tail);
t_arr       str_fjoin(t_arr head, t_arr tail);
size_t      str_clen(char* str);
size_t      str_len(t_arr str);
t_arr       str_dup(t_arr str, size_t len);
t_arr       str_sub(t_arr str, size_t start, size_t length);
t_arr       str_split(t_arr str, char sep);
t_arr       str_whitespace(t_arr str);
t_arr       str_fill(char c, size_t len);
t_char_a    str_char_to_str(char c);
int         str_chr(t_arr str, char c);

#endif