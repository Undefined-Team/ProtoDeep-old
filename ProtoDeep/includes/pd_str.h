#ifndef PD_STR_H
# define PD_STR_H

// Lib

// Macro

// Structures
typedef struct              pds_split_list {
    pd_arr                  word;
    struct pds_split_list   *next;
}                           pd_split_list;

// Prototypes
pd_arr                      pd_str_join(pd_arr head, pd_arr tail);
pd_arr                      pd_str_fjoin(pd_arr head, pd_arr tail);
size_t                      pd_str_clen(char* str);
size_t                      pd_str_len(pd_arr str);
pd_arr                      pd_str_dup(pd_arr str, size_t len);
pd_arr                      pd_str_sub(pd_arr str, size_t start, size_t length);
pd_arr                      pd_str_fsub(pd_arr str, size_t start, size_t length);
pd_arr                      pd_str_split(pd_arr str, char sep, int escape);
pd_arr                      pd_str_escape(pd_arr str);
pd_arr                      pd_str_whitespace(pd_arr str);
pd_arr                      pd_str_fill(char c, size_t len);
pd_char_a                   pd_str_char_to_str(char c);
int                         pd_str_chr(pd_arr str, char c);
int		                    pd_str_cmp(const char *s1, const char *s2);

#endif