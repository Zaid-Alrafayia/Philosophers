NAME = philo
SRCS = philo.c utils.c args.c utils_time.c init.c routine.c thread_routine.c

CC = cc
CFLAGS =  -Wall -Wextra -Werror -g -pthread
OBJS = $(SRCS:.c=.o)
all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
clean:
	rm -f $(OBJS)
fclean:clean
	rm -f $(NAME)
re: fclean $(NAME)
.PHONY: all clean fclean re
