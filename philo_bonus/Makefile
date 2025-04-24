# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ale-tell <ale-tell@42student.fr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/05 21:31:05 by ale-tell          #+#    #+#              #
#    Updated: 2024/12/10 18:27:10 by ale-tell         ###   ########.fr        #
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
		$(CDIR)/ft_atoi.c

## Compile ###
OBJ = $(patsubst $(CDIR)/%.c, $(ODIR)/%.o, $(SRC))
CFLAGS = -Wall -Wextra -Werror -pthread -I$(HDIR)
# CFLAGS = -pthread -g3 -I$(HDIR)

all: $(NAME)

$(ODIR)/%.o: $(CDIR)/%.c | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $^ $(CFLAGS) -o $@

test: re
	./test.sh


vtest: re
	# valgrind --show-leak-kinds=all --leak-check=full ./$(NAME) 4 800 200 200 2
	valgrind --trace-children=yes ./$(NAME) 4 1310 200 200

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
