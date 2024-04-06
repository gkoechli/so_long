NAME = so_long

OBJS = ${SRC:.c=.o}

FLAGS = -Wall -Werror -Wextra -g

OPTIONS = -lX11 -lXext

SRC = so_long.c	\
      utils.c	\
      utils_2.c	\
      mapcheck_error.c	\
      gnl.c	\
      gnl_utils.c	\
	  ft_bzero.c	\
	  ft_calloc.c	\
	  utils_3.c

$(NAME): $(OBJS)
	$(MAKE) -C ./mlx/minilibx-linux/
	gcc ${FLAGS} ${SRC} ./mlx/minilibx-linux/libmlx_Linux.a ${OPTIONS} -o ${NAME}

.c.o:
	gcc ${FLAGS} -c $< -o ${<:.c=.o}

all: ${NAME}
clean:
	rm -f ${OBJS}
fclean: clean
	rm -f ${NAME}
	$(MAKE) -C ./mlx/minilibx-linux/ clean
re: fclean all

.PHONY: all clean fclean re
