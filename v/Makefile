HOME		=   /nfs/zfs-student-4/users/2014_paris/rclanget/
SRC_PATH	=	./srcs/
SRC_NAME	=	draw_line.c free.c get_elem.c main.c parse_ant.c print.c event.c ft_global.c lst.c parse.c parse_link.c print_ants.c
OBJ_PATH	=	./obj/
INC_PATH	=	./include/ ./libft/includes/ $(HOME).brew/include/  
NAME		=	./viewer
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

OBJ_NAME	=	$(SRC_NAME:.c=.o)
SRC			=	$(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ			=	$(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC			=	$(addprefix -I,$(INC_PATH)) 
LIB_NAMES	=	./libft/libft.a -L $(HOME).brew/lib -lcsfml-system  -lcsfml-graphics -lcsfml-network -lcsfml-audio -Wl,-rpath,$(HOME).brew/lib
LDFLAGS		=	$(LIB_NAMES)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(INC) $(LDFLAGS) $(OBJ) -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
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

brew:
	brew update && brew upgrade
	brew install csfml

norme:
	norminette $(SRC)
	norminette $(INC_PATH)*.h
 