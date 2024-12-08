SRCS = main.c utils.c
CC = cc -Wall -Werror -Wextra -g3
DIRLIB = ./libft
LIBFT = $(DIRLIB)/libft.a
INCLUDE = ./include
NAME =	pipex
OBJS =	$(SRCS:.c=.o)

all :  $(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "pipex done !"

$(LIBFT) :
	@make -sC $(DIRLIB)

%.o : %.c
	@$(CC) -c $< -o $@
	@echo "compiling: $<"

clean :
	@make clean -sC $(DIRLIB)
	@rm -f $(OBJS)


fclean : clean
	@make fclean -sC $(DIRLIB)
	@rm -f $(NAME)

re : fclean all