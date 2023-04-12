CC := cc
CFLAGS := -Wall -Werror -Wextra
AR := ar rc
RM := rm -f
MAKEFLAGS := --no-print-directory

NAME := ../../lib/libftfprintf.a
INCLUDE := -I ../../includes/
HEADER := ../../includes/ft_fprintf.h
OBJ_DIR := ../../obj/ft_fprintf/

SRCS := ft_fprintf.c	\
	handle.c	\
	sublibft.c
OBJS = $(addprefix $(OBJ_DIR),$(SRCS:%.c=%.o))

BLUE = $(shell tput -Txterm setaf 6)
PURPLE = $(shell tput -Txterm setaf 5)
RED = $(shell tput -Txterm setaf 1)
RESET = $(shell tput -Txterm sgr0)

BOLD := $(shell tput bold)
SGR0 := $(shell tput sgr0)

SYMB := $(BOLD)$(BLUE)√$(SGR0)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $@ $^

$(OBJ_DIR)%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@printf "%-150s\r" "$(CC) $(CFLAGS) $(INCLUDE) -c $(BOLD)$(PURPLE)$<$(SGR0) -o $(BOLD)$(BLUE)$@$(SGR0)"

clean:
	@$(RM) $(OBJS)
fclean: clean
	@$(RM) $(NAME)
re: fclean all