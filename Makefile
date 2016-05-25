#*****************************************************************************#
#
#	- Akhenaton: Solveur de problème d'échecs -
# 	- L2 Imperatif Bourdin 2014/2015 -
#
#	Harry & Fode
#
#*****************************************************************************#

NAME =		lzw

W_FLAGS =	-Wall -Wextra

SRC_DIR =	src/
INC_DIR =	inc/

HEADER =	lzw_p8.h
FILES =		main.c init.c bits.c compress.c dico.c str_functions.c decompress.c \
			strlst.c charlst.c

SRC = 		$(addprefix $(SRC_DIR), $(FILES))
OBJ = 		$(SRC:.c=.o)

INC =		-I $(INC_DIR)

all:		$(NAME)


$(NAME):	$(OBJ)
			gcc -o $@ $^ $(INC)

%.o:		%.c $(INC_DIR)$(HEADER)
			gcc $(W_FLAGS) -o $@ -c $< $(INC)

clean:
			rm -f $(OBJ)

fclean: 	clean
			rm -f $(NAME)

re: 		fclean all

.PHONY:		all clean fclean re