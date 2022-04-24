NAME			= test
DNAME			= test_debug
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror

INCLUDE			= -I./includes/
LIBFLAG			= -I../includes/ -L./
RM				= rm -rf
OBJDIR			= ./obj/
SRCDIR			= ./src/
LIBDIR			= ../
DEBUG			= -g3 -fsanitize=address
MAIN			= main.c
TLIBNAME		= libexpr.a
SRCS			= tester.c

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

$(NAME):		$(SRCS_OBJS) $(MAIN_OBJS) $(TLIBNAME)
				@$(CC) $(CFLAGS) $(INCLUDE) $(LIBFLAG) -l$(TLIBNAME) $(MAIN_OBJS) $(SRCS_OBJS) -o $(NAME)
				@echo "\033[0;92m* $(NAME) was created *\033[0m"

$(TLIBNAME):	
				@$(MAKE) -C $(LIBDIR)
				@cp ../libexpr.a ./

debug:			objd_build	$(NAME)

$(DNAME):		$(SRCS_OBJS) $(MAIN_OBJS)
				$(CC) $(CFLAGS) $(DEBUG) $(INCLUDE) $(MAIN_OBJS) $(SRCS_OBJS) -o $(NAME)
				@echo "\033[0;92m* $(NAME) was created *\033[0m"

clean:
				@$(MAKE) -C $(LIBDIR) clean
				@$(RM) $(OBJDIR)
				@$(RM) $(OBJS)
				@echo "\033[0;91m* $(NAME)'s object files were removed *\033[0m"

fclean:			
				@$(MAKE) -C $(LIBDIR) fclean
				@$(MAKE) clean
				@$(RM) $(NAME)
				@echo "\033[0;91m* $(NAME) was removed *\033[0m"

re:				
				@$(MAKE) -C $(LIBDIR) re
				@$(MAKE) fclean
				@$(MAKE) all
				@echo "\033[0;91m* $(NAME) was re-created *\033[0m"


.PHONY:			all clean fclean re bonus