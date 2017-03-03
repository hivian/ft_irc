NAME_S 		= serveur
NAME_C		= client
CC 	 		= clang
#-Wall -Wextra -Werror

SRC			= srcs/

SRC_S  		= $(SRC)server/main.c \
			  $(SRC)server/init.c \
			  $(SRC)server/server.c \
			  $(SRC)server/cmd.c \
			  $(SRC)server/list_cmd.c \
			  $(SRC)server/util.c \

SRC_C		= $(SRC)client/main.c \
			  $(SRC)client/init.c \
			  $(SRC)client/client.c \
			  $(SRC)client/cmd.c \
			  $(SRC)client/list_cmd.c \
			  $(SRC)client/util.c \

OBJ_S  		= $(SRC_S:%.c=%.o)
OBJ_C		= $(SRC_C:%.c=%.o)

LIBFT 		= libft/libft.a
SRC_SDIR	= srcs/server
SRC_CDIR	= srcs/client
INC_DIR		= incs

WHITE		=	\033[0m
GREEN		=	\033[32m
BLUE		=	\033[1;34m
CYAN		=	\033[36m
RED			=	\033[31m
GREY		=	\033[1;30m
YELLOW		=	\033[33m

all: $(NAME_S) $(NAME_C)

$(LIBFT):
	@clear
	@printf "Compiling libft ... "
	@make -C libft/
	@echo "Done"

$(NAME_S): $(OBJ_S) $(LIBFT)
	@printf "Compiling server ... "
	@$(CC) $(CFLAGS) -o $(NAME_S) $(OBJ_S) $(LIBFT)
	@echo "Done"

$(NAME_C): $(OBJ_C) $(LIBFT)
	@printf "Compiling client ... "
	@$(CC) $(CFLAGS) -o $(NAME_C) $(OBJ_C) $(LIBFT)
	@echo "Done"

%.o: %.c
	@$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ -c $<

clean:
	@rm -f $(OBJ_S) $(OBJ_C)
	@make clean -C libft/

fclean: clean
	@rm -f $(NAME_S)
	@rm -f $(NAME_C)
	@make fclean -C libft/

re: fclean all

norm :
	@make -C libft/ norm
	@norminette $(SRC_S) $(SRC_C) $(INC_DIR)

.PHONY: all clean fclean re
