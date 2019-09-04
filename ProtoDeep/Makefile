NAME 			=	protodeep

CC 				= 	gcc
FLAGS 			=  -g -O3
INCLUDES		=	./includes/

SRC_PATH		=	./srcs/
BIN_PATH		=	./bins/

SRC 			= 	main.c				\

MATH_FLD		=	math/
MATH			=	math_log.c			\
					math_exp.c			\
					math_pow.c			\
					math_sqrt.c			\
					math_activation.c	\
					math_max.c			\
					math_min.c			\
					math_max_a.c 		\
					math_min_a.c 		\
					math_atof.c 		\
					math_mean.c 		\
					math_stdev.c 		\
					math_si_sort.c 		\
					math_itoa.c			\

STR_FLD			=	str/
STR				=	str_len.c			\
					str_clen.c			\
					str_join.c			\
					str_fjoin.c			\
					str_dup.c			\
					str_sub.c			\
					str_fsub.c			\
					str_split.c			\
					str_escape.c		\
					str_whitespace.c	\
					str_fill.c			\
					str_char_to_str.c	\
					str_chr.c			\
					str_cmp.c 			\

DAST_FLD		=	dast/
DAST			=	dast_free.c 		\
					dast_arr.c			\
					dast_time.c			\

PREP_FLD		=	csv/prep/
PREP			=	prep_minmax_scal.c	\
					prep_stdiz.c		\
					prep_ohe_init.c		\
					prep_ohe.c			\
					prep_delete.c		\
					prep_init_conf.c 	\
					prep_prepare.c		\
					prep_all_to_float.c	\
					prep_csv_split.c	\
					prep_tbnode.c		\
					prep_name_sort.c	\

CSV_FLD			=	csv/csv/
CSV				=	csv_read.c			\
					csv_tokens.c		\
					csv_cols.c			\
					csv_free.c 			\
					csv_print.c 		\

TENS_FLD		=	tens/
TENS			=	tens_init.c			\
					tens_get_shape.c	\
					tens_concat.c 		\
					tens_print.c 		\
					tens_copy.c 		\
					tens_free.c 		\

NN_FLD			=	nn/
NN				=	nn_config.c			\
					nn_dense.c			\
					nn_print.c			\
					#nn_forward.c

SRC_FLDS		=	math/				\
					str/				\
					dast/				\
					csv/				\
					csv/csv/			\
					csv/prep/			\
					tens/				\
					nn/					\

SRC				+=	$(addprefix $(MATH_FLD), $(MATH))
SRC				+=	$(addprefix $(PREP_FLD), $(PREP))
SRC				+=	$(addprefix $(CSV_FLD), $(CSV))
SRC				+=	$(addprefix $(STR_FLD), $(STR))
SRC				+=	$(addprefix $(DAST_FLD), $(DAST))
SRC				+=	$(addprefix $(TENS_FLD), $(TENS))
SRC				+=	$(addprefix $(NN_FLD), $(NN))

BIN				=	$(SRC:.c=.o)
BIN_FLDS		=	$(addprefix $(BIN_PATH), $(SRC_FLDS))

SRCS			=	$(addprefix $(SRC_PATH), $(SRC))
BINS			=	$(addprefix $(BIN_PATH), $(BIN))

OBJ 			= 	$(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(BIN_PATH) $(BIN_FLDS) $(BINS)
	$(CC) $(FLAGS) $(BINS) -o $@

$(BIN_PATH):
	mkdir $(BIN_PATH)
	
$(BIN_FLDS):
	mkdir $@
	
$(BIN_PATH)%.o: $(SRC_PATH)%.c $(INCLUDES)
	$(CC) $(FLAGS) -I includes -o $@ -c $<

%.o: %.c
		$(CC) -I $(INCLUDES) -o $@ -c $< $(FLAGS)

clean:
		rm -Rf $(BIN_PATH)

fclean: clean
		rm -f $(NAME)

re: fclean all

ex: all
	./$(NAME)

rex: re
	./$(NAME)

vex: all
	valgrind --leak-check=full ./protodeep
