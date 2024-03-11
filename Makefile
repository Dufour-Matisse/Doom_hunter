##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## feur
##

SRC = my_hunter.c \
	  window.c \
	  weapon.c \
	  mob.c \
	  my_random.c \
	  my_strncmp.c \
	  minilib.c \
	  cursor.c \
	  event.c \
	  menu.c \
	  score.c

OBJ = $(SRC:.c=.o)

CFLAGS += -Wall -Wextra -Werror -Iinclude

NAME = my_hunter

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS) -lcsfml-graphics -lcsfml-system -g

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
