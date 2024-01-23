#Program variables
NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra

#Files variables
LIBFT = sources/libft
SRCS_FILES =	main.c \
				pipex.c \
				utils.c
SRCS = $(addprefix sources/, $(SRCS_FILES))
OBJS = $(SRCS:.c=.o)
INCLS = includes/

#Extra variables
RESET = \033[1;39m
BOLD= \033[1m
GREEN= \033[1;32m
BLUE= \033[1;34m

#Commands
all : $(NAME)

libft :
	@make bonus -C $(LIBFT) --no-print-directory

$(NAME) : libft display $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT)/libft.a
	@echo "$(BOLD)]$(RESET)"

%.o : %.c
	@$(CC) $(CFLAGS) -o $@ -c $< -I$(INCLS)
	@echo -n "$(BOLD)$(BLUE)#$(RESET)"

clean :
	@make clean -C $(LIBFT) --no-print-directory
	@rm -f $(OBJS)
	@echo "$(BOLD)[$(NAME)]		$(GREEN)object files removed$(RESET)"

fclean : clean
	@make fclean -C $(LIBFT) --no-print-directory
	@rm -f $(NAME)
	@echo "$(BOLD)[$(NAME)]		$(GREEN)binary file removed$(RESET)"

re : fclean all

display :
	@echo -n "$(BOLD)[$(NAME)]		[$(RESET)"

.PHONY : all clean fclean re display