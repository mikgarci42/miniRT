.DEFAULT_GOAL = all

FILES = create_tuple	\
	operation_tuple	\
	operation_tuple_two	\
	error	\
	world	\
	world_two	\
	color	\
	cube	\
	camera	\
	cylinder	\
	ray		\
	sphere	\
	plane	\
	intersections	\
	materials	\
	patterns	\
	lights	\
	matrix_utils	\
	matrix_det		\
	matrix_inver		\
	matrix_trans	\
	matrix_trans_two	\

NAME = algft.a
ALGH = algft.h
SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = inc/
AR = ar rcs
CC = gcc
CFLAGS = -g3 -Wall -Wextra -Werror
ARFLAGS = -rcuvs
ARLFLAGS = -tv
RANLIB = ranlib
MKDIR = mkdir -p

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

$(OBJ_DIR): 
	$(MKDIR) $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_DIR)$(ALGH) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJ)
	$(AR) $@ $(OBJ)
	$(RANLIB) $(NAME)

all: $(NAME)

clean:
	-$(RM) -r $(OBJ_DIR)

fclean: clean
	-$(RM) $(NAME)

re: fclean all

list:
	$(AR) $(ARLFLAGS) $(NAME)

.PHONY: all clean fclean re list
