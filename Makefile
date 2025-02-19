CC := cc
CFLAGS := -Wall -Werror -Wextra
CFLAGS_DB := -Wall -Werror -Wextra -g3
CFLAGS_NE := -g3

LIBFT_DIR := ./libft
LIBFT_AR := $(LIBFT_DIR)/libft.a
LIBFT_FLAGS := -lft -L$(LIBFT_DIR)

NAME := push_swap

SRC_DIR := src
vpath %.h %.c $(SRC_DIR)
HEADER := push_swap.h
SRC := push_swap.c

OBJ_DIR := build
OBJ := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))


all: $(OBJ_DIR) ft $(NAME)
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
noerr: CFLAGS = $(CFLAGS_NE)
noerr: all
dbg: CFLAGS = $(CFLAGS_DB)
dbg: all
ft:
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBFT_FLAGS)

$(OBJ_DIR)/%.o: %.c Makefile $(HEADER) $(LIBFT_AR)
	$(CC) -c $< -o $@

clean:
	-rm $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	-rm $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all ft clean fclean re noerr dbg
