CC := cc
CFLAGS := -Wall -Werror -Wextra
CFLAGS_DB := -Wall -Werror -Wextra -g3
CFLAGS_NE := -g3

LIBFT_DIR := ./libft
LIBFT_AR := $(LIBFT_DIR)/libft.a
LIBFT_FLAGS := -lft -L$(LIBFT_DIR)

NAME := push_swap

SRC_DIR := src
vpath %.h $(SRC_DIR)
HEADER := push_swap.h
vpath %.c $(SRC_DIR)
SRC := push_swap.c \
       lst_utils.c \
       free_exit.c \
       parsing.c \
       data_collect.c \
       list_operations.c \
       stack_operations.c

OBJ_DIR := build
OBJ := $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))


all: $(OBJ_DIR) ft $(NAME)
$(OBJ_DIR):
	# git submodule init
	# git submodule update
	mkdir -p $(OBJ_DIR)
noerr: CFLAGS = $(CFLAGS_NE)
noerr: all
dbg: CFLAGS = $(CFLAGS_DB)
dbg: all
ft:
	make CFLAGS="$(CFLAGS)" -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(CC) $^ -o $@ $(LIBFT_FLAGS)

$(OBJ_DIR)/%.o: %.c Makefile $(HEADER) $(LIBFT_AR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)

fclean:
	make fclean -C $(LIBFT_DIR)
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all ft clean fclean re noerr dbg
