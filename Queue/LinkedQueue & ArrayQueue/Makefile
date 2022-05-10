AQNAME			= queueTester_aq
LQNAME			= queueTester_lq
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror
INCLUDE			= -I./includes/
RM				= rm -rf
OBJDIR			= ./obj/
SRCDIR			= ./srcs/
DEBUG			= -g3 -fsanitize=address
AQMAIN			= AQmain.c
LQMAIN			= LQmain.c
SRCS			= arrayQueue.c linkedDeque.c

AQMAIN_OBJS_FILE= $(AQMAIN:.c=.o)
AQMAIN_OBJS		= $(addprefix $(OBJDIR), $(AQMAIN_OBJS_FILE))

LQMAIN_OBJS_FILE= $(LQMAIN:.c=.o)
LQMAIN_OBJS		= $(addprefix $(OBJDIR), $(LQMAIN_OBJS_FILE))

SRCS_OBJS_FILE	= $(SRCS:.c=.o)
SRCS_OBJS		= $(addprefix $(OBJDIR), $(SRCS_OBJS_FILE))

aq:			objd_build	$(AQNAME)

objd_build:
				mkdir -p $(OBJDIR)

$(OBJDIR)%.o : ./%.c
				$(CC) $(CFLAGS) $(INCLUDE) $< -c -o $@

$(OBJDIR)%.o : $(SRCDIR)%.c
				$(CC) $(CFLAGS) $(INCLUDE) $< -c -o $@

$(AQNAME):		$(SRCS_OBJS) $(AQMAIN_OBJS)
				$(CC) $(CFLAGS) $(INCLUDE) $(AQMAIN_OBJS) $(SRCS_OBJS) -o $(AQNAME)
				@echo "\033[0;92m* $(AQNAME) was created *\033[0m"

lq:			objd_build	$(LQNAME)

objd_build:
				mkdir -p $(OBJDIR)

$(OBJDIR)%.o : ./%.c
				$(CC) $(CFLAGS) $(INCLUDE) $< -c -o $@

$(OBJDIR)%.o : $(SRCDIR)%.c
				$(CC) $(CFLAGS) $(INCLUDE) $< -c -o $@

$(LQNAME):		$(SRCS_OBJS) $(LQMAIN_OBJS)
				$(CC) $(CFLAGS) $(INCLUDE) $(LQMAIN_OBJS) $(SRCS_OBJS) -o $(LQNAME)
				@echo "\033[0;92m* $(LQNAME) was created *\033[0m"


clean:
				@$(RM) $(OBJDIR)
				@$(RM) $(OBJS)

fclean:			
				@$(MAKE) clean
				@$(RM) $(LQNAME) $(AQNAME)
				@echo "\033[0;91m* all testers was removed *\033[0m"

.PHONY:			all clean fclean