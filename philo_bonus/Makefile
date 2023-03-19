NAME = philo_bonus

SRCS = philo_utils_bonus.c \
	   philo_utils1_bonus.c \
	   philo_utils2_bonus.c \
	   philo_bonus.c \
	   parsing_bonus.c \


OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Werror -Wextra

CC = gcc

all: $(NAME) philo_bonus.h

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $@

%.o : %.c
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all