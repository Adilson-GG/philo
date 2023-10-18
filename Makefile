CC = gcc

CFLAGS = -Wall -Wextra -Werror 

NAME = philo

SRC_PATH = sources/

OBJ_PATH = objets/

SRC = philo.c errors.c start.c utils.c

OBJ = $(SRC:.c=.o)

OBJ_DIR = objets

SRC_DIR = sources

PREFC = $(addprefix $(SRC_PATH), $(SRC))

PREFO = $(addprefix $(OBJ_PATH), $(OBJ))

all : $(NAME)


$(NAME) : $(PREFO)
	@$(CC) $(CFLAGS)  -o $(NAME) $(PREFO) -g3 -lpthread
	@echo "Compilation terminee !"


$(OBJ_PATH)%.o : $(SRC_PATH)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $<

clean :
	@rm -rf $(OBJ_DIR)
	@echo "------->  Au revoir les .o."

fclean : clean
	@rm -f $(NAME)
	@echo "--------> Tout est a la poubelle, chef !"

re : fclean all

.PHONY : all clean fclean re