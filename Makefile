NAME = so_long

OBJS = ${SRC:.c=.o}

FLAGS = -Wall -Werror -Wextra -g

OPTIONS = -lX11 -lXext

SRC = srcs/so_long.c	\
      srcs/utils.c	\
      srcs/utils_2.c	\
      srcs/mapcheck_error.c	\
      srcs/gnl.c	\
      srcs/gnl_utils.c	\
	  srcs/ft_bzero.c	\
	  srcs/ft_calloc.c	\
	  srcs/utils_3.c

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
