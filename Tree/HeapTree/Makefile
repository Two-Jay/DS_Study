NAME			= heap
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

INCLUDE			= -I./includes/
RM				= rm -rf
OBJDIR			= ./obj/
SRCDIR			= ./srcs/
DEBUG			= -g
SRCS			= main.c heap.c

SRCS_OBJS_FILE	= $(SRCS:.c=.o)
SRCS_OBJS		= $(addprefix $(OBJDIR), $(SRCS_OBJS_FILE))

all:			objd_build	$(NAME)

objd_build:
				mkdir -p $(OBJDIR)

$(OBJDIR)%.o : $(SRCDIR)%.c
				$(CC) $(CFLAGS) $(DEBUG) $(INCLUDE) $< -c -o $@

$(NAME):		$(SRCS_OBJS)
				$(CC) $(CFLAGS) $(DEBUG) $(INCLUDE) $(SRCS_OBJS) -o $(NAME)
				@echo "\033[0;92m* $(NAME) was created *\033[0m"

clean:
				@$(RM) $(OBJDIR)
				@$(RM) $(OBJS)

fclean:			
				@$(MAKE) clean
				@$(RM) $(NAME)
				@echo "\033[0;91m* $(NAME) was removed *\033[0m"

re:				
				@$(MAKE) fclean
				@$(MAKE) all


.PHONY:			all clean fclean re bonus