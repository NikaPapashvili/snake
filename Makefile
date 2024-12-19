NAME = snake

CC = cc

CFLAGS += -Wall -Werror -Wextra

SRC =	game_mode.c \
		map.c \
		overlay.c \
		render_manager.c \
		render_utils.c \
		snake.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): ${OBJ}
	${CC} -o ${NAME} ${OBJ} -lSDL2 -lSDL2_ttf -lm
	
clean:
	rm -rf ${OBJ}

fclean: clean
	rm -rf ${NAME}

re: fclean all
