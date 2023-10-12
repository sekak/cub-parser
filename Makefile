NAME = parser
HEADER = parser.h
FILES = parser.c get_next_line.c get_next_line_utils.c map.c

FILES_O = $(FILES:.c=.o)
LIBFT = ./libft/libft.a

all: $(NAME)

$(LIBFT):
	make -C libft

%.o: %.c	
	gcc -Wall -Wextra -Werror -fsanitize=address -g -Ilibft -c $< -o $@

$(NAME): $(FILES_O) $(LIBFT)	
	gcc $(FILES_O) -Wall -Wextra -Werror -fsanitize=address -g $(LIBFT) -o $(NAME)

clean:
	rm -rf $(FILES_O)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re