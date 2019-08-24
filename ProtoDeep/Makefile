NAME 		=	protodeep

CC 			= 	gcc
FLAGS 		= 	-Wall -Wextra -Werror -g -O3
INCLUDES	=	./includes/

SRC_PATH	=	./srcs/
BIN_PATH	=	./bins/

SRC 		= 	main.c		\

MATH_FLD	=	math/
MATH		=	math_log.c			\
				math_exp.c			\
				math_pow.c			\
				math_sqrt.c			\
				math_activation.c	\

SRC_FLDS	=	math/		\

SRC 		+=	$(addprefix $(MATH_FLD), $(MATH))

BIN			=	$(SRC:.c=.o)
BIN_FLDS	=	$(addprefix $(BIN_PATH), $(SRC_FLDS))

SRCS		=	$(addprefix $(SRC_PATH), $(SRC))
BINS		=	$(addprefix $(BIN_PATH), $(BIN))

OBJ = $(SRCS:.c=.o)

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
