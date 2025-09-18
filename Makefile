NAME = pipex

SOURCES = pipex.c free_split.c process.c 

OBJECTS = $(SOURCES:.c=.o)
LIBFT = ./libft/libft.a

CC = cc
DBGFLAGS = -g
CFLAGS = -Wall -Wextra -Werror -I./include -I./libft
LDFLAGS = -L./libft/ -lft

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o $(NAME)

dbg: CFLAGS += $(DBGFLAGS)
dbg: re
$(LIBFT):
	make -C libft

clean:
	rm -f $(OBJECTS)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re dbg