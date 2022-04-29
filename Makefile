FILES = main	\
		parse/parse	\
		parse/parse_info \
		parse/parse_utils \
		parse/parse_obj

NAME = miniRT

INC = -I ./algft/inc -I ./libft

#CFLAGS = -g3 -Wextra -Werror -Wall
CFLAGS = -g3 -fsanitize=address -Wextra -Werror -Wall
XFLAGS = -L . -lmlx -framework OpenGL -framework AppKit

S = ./
SRCS = $(addprefix $(S), $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(S), $(addsuffix .o, $(FILES)))

$(NAME): $(OBJS)
		$(MAKE) -C ./minilibx
		$(MAKE) -C ./algft
		$(MAKE) -C ./libft
		cp ./minilibx/libmlx.a .
		cp ./algft/algft.a .
		cp ./libft/libft.a .
		$(CC) $(CFLAGS) $(XFLAGS) $(INC) $(OBJS) algft.a libft.a -o $(NAME)

all: $(NAME)

clean:
		$(RM) $(OBJS)
		$(MAKE) clean -C ./minilibx
		$(MAKE) clean -C ./algft
		rm -rf *.swp

fclean: clean
		$(MAKE) fclean -C ./algft
		$(RM) $(NAME)
		$(RM) *.a
		$(RM) -r *.dSYM

re: fclean all

.PHONY: all re clean fclean
