NAME			= bankSimul
DNAME			= test_debug
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror
INCLUDE			= -I./includes/
RM				= rm -rf
OBJDIR			= ./obj/
SRCDIR			= ./src/
DEBUG			= -g3 -fsanitize=address
MAIN			= main.c
SRCS			= polynomialList.c parser.c

MAIN_OBJS_FILE	= $(MAIN:.c=.o)
MAIN_OBJS		= $(addprefix $(OBJDIR), $(MAIN_OBJS_FILE))

SRCS_OBJS_FILE	= $(SRCS:.c=.o)
SRCS_OBJS		= $(addprefix $(OBJDIR), $(SRCS_OBJS_FILE))

all:			objd_build	$(NAME)

objd_build:
				mkdir -p $(OBJDIR)

$(OBJDIR)%.o : ./%.c
				$(CC) $(CFLAGS) $(INCLUDE) $< -c -o $@

$(OBJDIR)%.o : $(SRCDIR)%.c
				$(CC) $(CFLAGS) $(INCLUDE) $< -c -o $@

$(NAME):		$(SRCS_OBJS) $(MAIN_OBJS)
				$(CC) $(CFLAGS) $(INCLUDE) $(MAIN_OBJS) $(SRCS_OBJS) -o $(NAME)
				@echo "\033[0;92m* $(NAME) was created *\033[0m"

debug:			objd_build	$(NAME)

$(DNAME):		$(SRCS_OBJS) $(MAIN_OBJS)
				$(CC) $(CFLAGS) $(DEBUG) $(INCLUDE) $(MAIN_OBJS) $(SRCS_OBJS) -o $(NAME)
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