

SRC_PATH	=	./srcs/
SRC_NAME	=	*.c
OBJ_PATH	=	./obj/
INC_PATH	=	./include/ ./libft/includes/ ~/.brew/include
NAME		=	./viewer
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

OBJ_NAME	=	$(SRC_NAME:.c=.o)
SRC			=	$(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ			=	$(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC			=	$(addprefix -I,$(INC_PATH))
LIB_NAMES	=	./libft/libft.a -L ~/.brew/lib -lcsfml-system -lcsfml-window -lcsfml-graphics -lcsfml-network -lcsfml-audio -Wl,-rpath,$HOME/.brew/lib
LDFLAGS		=	$(LIB_NAMES) 
all: $(NAME)

$(NAME): 
	make -C libft
	$(CC) $(CFLAGS) $(SRC_PATH)* $(INC) $(LDFLAGS) -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(OBJ_PATH)
	echo "coco"; $(CC) $(CFLAGS) -o $@ -c $<

clean:
	@make clean -C libft
	@rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null

fclean: clean
	@make fclean -C libft
	@rm -fv $(NAME)

re: fclean all

norme:
	norminette $(SRC)
	norminette $(INC_PATH)*.h
