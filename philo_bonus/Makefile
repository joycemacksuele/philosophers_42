# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/19 00:38:15 by jfreitas          #+#    #+#              #
#    Updated: 2021/08/11 22:17:12 by whoami           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

##### COLORS #####
WHITE = \033[1;37m
GREY = \033[1;30m
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
LIGHT_BLUE = \033[1;36m
END = \033[0m

##### OSTYPE #####
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	# Mac
	FLAGS += -D DARWIN
else
	#Linux
	FLAGS += -D LINUX
endif

##### FLAG #####
CC = clang
FLAGS = -Wall -Wextra -Werror -g -pthread -fsanitize=address

##### SRC & OBJ PATH #####
UTILSPATH = ../philo_bonus/srcs
SRCPATH = ./srcs
OBJPATH = $(SRCPATH)/objs

##### INCLUDE #####
INC_PHILO_ONE = ./includes

##### INCLUDES DEPENDENCIES ####
# ->  Any modify to a .h file will alert Makefile to recompile
INC_DEP = $(INC_PHILO_ONE)/*.h

##### SOURCES #####
SRCS = $(addprefix $(SRCPATH)/, main.c ft_functions.c philo_bonus.c \
	init_args_data.c init_process_semaphore.c time.c print.c inspector.c \
	exit_and_error.c)

##### OBJECTS #####
OBJS = $(SRCS:$(SRCPATH)/%.c=$(OBJPATH)/%.o)

#### RULES ####
all: mk_objdir $(NAME)

mk_objdir:
	@if [ ! -d $(OBJPATH) ]; then mkdir $(OBJPATH); fi

$(NAME): $(OBJS) $(INC_DEP)
	@echo "\n$(END)$(LIGHT_BLUE)Making $(NAME)$(END)"
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS)
	@echo "$(END)$(GREEN)$(NAME) is built\n$(END)"

$(OBJPATH)/%.o: $(SRCPATH)/%.c $(INC_DEP)
	@$(CC) $(FLAGS) -I $(INC_PHILO_ONE) -c $< -o $@
# -c Runs all of the above, + the assembler, generating a target .o object file.
# $< Is for the $(SRCPATH)/%.c part and $@ for the $(OBJPATH)/%.o part.

### CLEAN ###
.PHONY: clean fclean re

clean:
	@echo "$(END)$(YELLOW)Removing $(NAME) object file$(END)"
	@rm -rf $(OBJPATH)
	@rm -rf $(OBJS_CHECKER)

fclean: clean
	@echo "$(END)$(YELLOW)\nRemoving $(NAME) binary$(END)"
	@rm -f $(NAME)

re: fclean all
