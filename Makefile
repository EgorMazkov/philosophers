NAME		=	philo

SRCS_FILES	= 	${shell find ./source -name "*.c"}

SRCS_FOLDER	=	source/

SRCS		= 	$(SRCS_FILES)
OBJS		=	$(patsubst %.c,%.o,$(SRCS))

INCLUDE		=	-I./include

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g
RM			=	rm -f

.PHONY:		all clean fclean re bonus

all:		$(NAME)

%.o:		%.c
			$(CC) $(CFLAGS) $(INCLUDE) -c -g $< -o $@
$(NAME):	$(OBJS)
			@$(CC) $(INCLUDE) -o $(NAME) $(OBJS)
			@echo "\033[36;1m\nCompiled\n\033[0m"

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

norm:
	norminette