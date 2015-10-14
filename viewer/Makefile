SRC_PATH	=	./srcs/
SRC_NAME	=	*.c
OBJ_PATH	=	./obj/
INC_PATH	=	./include/ ./libft/includes/ /nfs/zfs-student-4/users/2014_paris/rclanget/.brew/include/  
NAME		=	./viewer
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

OBJ_NAME	=	$(SRC_NAME:.c=.o)
SRC			=	$(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ			=	$(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC			=	$(addprefix -I,$(INC_PATH)) 
LIB_NAMES	=	-L /nfs/zfs-student-4/users/2014_paris/rclanget/.brew/lib -lcsfml-system -lcsfml-window -lcsfml-graphics -lcsfml-network -lcsfml-audio -Wl,-rpath,$HOME/.brew/lib
LDFLAGS		=	$(LIB_NAMES)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) $(INC) -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	make -C libft
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	make clean -C libft
	rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null

fclean: clean
	make fclean -C libft
	rm -fv $(NAME)

re: fclean all
	make re -C libft

norme:
	norminette $(SRC)
	norminette $(INC_PATH)*.h
 