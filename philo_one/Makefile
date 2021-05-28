# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfreitas <jfreitas@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/19 00:38:15 by jfreitas          #+#    #+#              #
#    Updated: 2021/05/22 02:46:22 by jfreitas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_one

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
FLAGS = -Wall -Wextra -Werror -g -pthread# -fsanitize=address -fsanitize=thread

##### SRC & OBJ PATH #####
UTILSPATH = ../philo_one/srcs
SRCPATH = ./srcs
OBJPATH = $(SRCPATH)/objs

##### INCLUDE #####
INC_PHILO_ONE = ./includes

##### INCLUDES DEPENDENCIES ####
# ->  Any modify to a .h file will alert Makefile to recompile
INC_DEP = $(INC_PHILO_ONE)/*.h

##### SOURCES #####
SRCS = $(addprefix $(SRCPATH)/, main.c philo_one.c init.c time.c)
UTILS = $(addprefix $(UTILSPATH)/, ft_functions.c)

##### OBJECTS #####
OBJS = $(SRCS:$(SRCPATH)/%.c=$(OBJPATH)/%.o)
#OBJS += $(UTILS:$(UTILSPATH)/%.c=$(OBJPATH)/%.o)
OBJS_UTILS = $(UTILS:$(UTILSPATH)/%.c=$(OBJPATH)/%.o)

#### RULES ####
all: mk_objdir $(NAME)

mk_objdir:
	@if [ ! -d $(OBJPATH) ]; then mkdir $(OBJPATH); fi

$(NAME): $(OBJS) $(INC_DEP) $(OBJS_UTILS)
	@echo "\n$(END)$(LIGHT_BLUE)Making $(NAME)$(END)"
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(OBJS_UTILS)
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
