FILES = main	\
		parse/parse	\
		parse/parse_info \
		parse/parse_utils \
		parse/parse_obj \
		parse/parse_obj_two

NAME = miniRT

INC = -I ./algft/inc -I ./libft

CFLAGS = -g3 -Wextra -Werror -Wall -fsanitize=address 
XFLAGS = -L . -lmlx -framework OpenGL -framework AppKit

S = ./
SRCS = $(addprefix $(S), $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(S), $(addsuffix .o, $(FILES)))

$(NAME): $(OBJS)
		$(MAKE) -C ./.minilibx
		$(MAKE) -C ./algft
		$(MAKE) -C ./libft
		cp ./.minilibx/libmlx.a .
		cp ./algft/algft.a .
		cp ./libft/libft.a .
		$(CC) $(CFLAGS) $(XFLAGS) $(INC) $(OBJS) algft.a libft.a -o $(NAME)

all: $(NAME)

clean:
		$(RM) $(OBJS)
		$(MAKE) clean -C ./.minilibx
		$(MAKE) clean -C ./algft
		$(MAKE) clean -C ./libft
		rm -rf *.swp

fclean: clean
		$(MAKE) fclean -C ./algft
		$(MAKE) fclean -C ./libft
		$(RM) $(NAME)
		$(RM) *.a
		$(RM) -r *.dSYM
		$(RM) -r .*.swp
		$(RM) -r *.swp

re: fclean all

.PHONY: all re clean fclean
