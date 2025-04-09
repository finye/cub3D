NAME = cub3D

SOURCES = main.c

OBJECTS = $(SOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	@$(CC) -c $(CFLAGS) $< -o $@

$(NAME): $(OBJECTS)
		@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

clean:
		@rm -f ${OBJECTS}

fclean: clean
		@rm -f ${NAME}
		
re : fclean all

.PHONY: all clean fclean re