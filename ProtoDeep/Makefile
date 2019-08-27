NAME 		=	protodeep

CC 			= 	gcc
FLAGS 		= 	-Wall -Wextra -Werror -g -O3
INCLUDES	=	./includes/

SRC_PATH	=	./srcs/
BIN_PATH	=	./bins/

SRC 		= 	main.c				\

MATH_FLD	=	math/
MATH		=	math_log.c			\
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

PREP_FLD	=	prep/
PREP		=	prep_minmax_scal.c	\
				prep_stdiz.c		\

CSV_FLD		=	csv/
CSV			=	csv_read.c		\

STR_FLD		=	str/
STR			=	str_len.c			\
				str_join.c			\
				str_dup.c			\
				str_sub.c			\
				str_split.c			\
				str_whitespace.c	\
				str_fill.c			\
				str_add_char.c		\
				str_char_to_str.c	\
				str_chr.c			\

DAST_FLD	=	dast/
DAST		=	dast_new_farr.c				\
				dast_new_tbnode.c 			\
				dast_new_carr.c				\
				dast_new_static_carr.c		\
				dast_free.c					\
				dast_csv_new_col.c			\
				dast_init_varr.c			\
				dast_arr.c					\

DBUG_FLD	=	dbug/
DBUG		=	dbug_print_csv.c			\
				

SRC_FLDS	=	math/				\
				prep/				\
				csv/				\
				str/				\
				dast/				\
				dbug/				\

SRC 		+=	$(addprefix $(MATH_FLD), $(MATH))
SRC 		+=	$(addprefix $(PREP_FLD), $(PREP))
SRC 		+=	$(addprefix $(CSV_FLD), $(CSV))
SRC 		+=	$(addprefix $(STR_FLD), $(STR))
SRC 		+=	$(addprefix $(DAST_FLD), $(DAST))
SRC 		+=	$(addprefix $(DBUG_FLD), $(DBUG))

BIN			=	$(SRC:.c=.o)
BIN_FLDS	=	$(addprefix $(BIN_PATH), $(SRC_FLDS))

SRCS		=	$(addprefix $(SRC_PATH), $(SRC))
BINS		=	$(addprefix $(BIN_PATH), $(BIN))

OBJ 		= 	$(SRCS:.c=.o)

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
