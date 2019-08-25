#ifndef PD_STR_H
# define PD_STR_H

// Lib

// Macro

// Structures

// Prototypes
char    *str_join(char *head, char *tail);
size_t  str_len(char *str);
char    *str_dup(char *str);
char    *str_sub(char *str, size_t start, size_t length);
char    **str_split(char *str, char sep);
char    *str_whitespace(char *str);

#endif