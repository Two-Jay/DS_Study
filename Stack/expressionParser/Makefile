LIBNAME			= libexpr.a
TESTER_NAME		= tester
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

INCLUDE			= -I./includes/
RM				= rm -rf
OBJDIR			= ./obj/
SRCDIR			= ./src/
DEBUG			= -g3 -fsanitize=address
SRCS			= farraystack.c expressionParser.c blankChecker.c

SRCS_OBJS_FILE	= $(SRCS:.c=.o)
SRCS_OBJS		= $(addprefix $(OBJDIR), $(SRCS_OBJS_FILE))

all:			objd_build	$(TESTER_NAME)

objd_build:
				mkdir -p $(OBJDIR)

$(OBJDIR)%.o : $(SRCDIR)%.c
				@$(CC) $(CFLAGS) $(INCLUDE) $< -c -o $@

$(TESTER_NAME):	$(SRCS_OBJS)
				@ar rc $(LIBNAME) $(SRCS_OBJS)
				@$(CC) $(CFLAGS) $(INCLUDE) main.c -o $(TESTER_NAME) libexpr.a
				@echo "\033[0;92m* $(TESTER_NAME) was created *\033[0m"

clean:
				@$(RM) $(OBJDIR)
				@$(RM) $(OBJS)
				@echo "\033[0;91m* $(TESTER_NAME)'s object files were removed *\033[0m"

fclean:			
				@$(MAKE) clean
				@$(RM) $(TESTER_NAME)
				@$(RM) $(LIBNAME)
				@echo "\033[0;91m* $(TESTER_NAME) was removed *\033[0m"

re:				
				@$(MAKE) fclean
				@$(MAKE) all
				@echo "\033[0;91m* $(TESTER_NAME) was re-created *\033[0m"


.PHONY:			all clean fclean re bonus