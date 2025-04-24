# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/05 21:31:05 by ale-tell          #+#    #+#              #
#    Updated: 2024/12/10 17:53:30 by ale-tell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc

CDIR = ./src
ODIR = ./obj
HDIR = ./include

SRC =	$(CDIR)/philo.c \
		$(CDIR)/messages.c \
		$(CDIR)/init.c \
		$(CDIR)/eat.c \
		$(CDIR)/death.c \
		$(CDIR)/time.c \
		$(CDIR)/forks.c \
		$(CDIR)/ft_atoi.c

### Compile ###
OBJ = $(patsubst $(CDIR)/%.c, $(ODIR)/%.o, $(SRC))
CFLAGS = -Wall -Wextra -Werror -pthread -I$(HDIR)

all: $(NAME)

$(ODIR)/%.o: $(CDIR)/%.c | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $^ $(CFLAGS) -o $@

test: re
	./test.sh

vtest: re
	# valgrind --show-leak-kinds=all --leak-check=full ./$(NAME) 4 800 200 200 2
	valgrind --tool=helgrind ./$(NAME) 4 1000 200 200
	# valgrind --tool=helgrind ./$(NAME) 3 1000 200 200 10

### Setup ###
$(ODIR):
	mkdir -p $@

init: 
	mkdir -p $(HDIR) $(CDIR) $(ODIR)

### Clean ###
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re test init vtest
