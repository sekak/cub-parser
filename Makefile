NAME = parser
Header = get_next_line.h

FILES = parser.c get_next_line.c get_next_line_utils.c

FILES_O = $(FILES:.c=.o)

%.o: %.c
	gcc -Wall -Wextra -Werror  -fsanitize=address -g -c $< -o $@

$(NAME): $(FILES_O)
		gcc $(FILES_O)  -Wall -Wextra -Werror -fsanitize=address -g -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(Files_O)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)

.PHONY: all bonus clean fclean re 