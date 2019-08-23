CC = gcc

NAME = test

SRCS = srcs/dp_math.c \
		srcs/main.c \

FLAGS = -Wall -Wextra -Werror -g -O3

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) -I includes -o $@ $^ $(FLAGS)

%.o: %.c
		$(CC) -I includes/ -o $@ -c $< $(FLAGS)

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

re: fclean all
