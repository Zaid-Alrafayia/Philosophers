NAME = philo

CC = cc

CC_FLAGS = -pthread -Wall -Werror -Wextra

SRCS = philo.c philo_utils.c

OBJS = $(SRCS:.c=.o)


all:$(NAME)

$(NAME):$(OBJS)
	$(CC) $(CC_FLAGS) $(OBJS) -o $(NAME)

%.o:%.c
	$(CC) $(CC_FLAGS) -I. -c $< -o $@

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(NAME) $(OBJS)

re : clean all

