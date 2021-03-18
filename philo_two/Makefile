# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: totartar <totartar@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/12/10 22:26:58 by totartar      #+#    #+#                  #
#    Updated: 2021/03/18 12:12:57 by totartar      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo_two

FLAGS = -Wall -Wextra -Werror -pthread

ifdef DEBUG
FLAGS += -g -fsanitize=thread
endif

SRC= env.c \
		error.c \
   		input.c \
   		logs.c \
   		main.c \
   		meals.c \
   		monitor.c \
   		semaphore.c \
   		philo.c \
   		thread.c \
   		time.c \
   		utils.c \

all: $(NAME)

COMPILER=gcc

$(NAME):
	$(COMPILER) $(FLAGS) $(SRC) -g -o $(NAME)

fclean:
	rm -f $(NAME)

re: fclean all
