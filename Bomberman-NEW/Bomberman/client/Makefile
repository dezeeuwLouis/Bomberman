CC =	gcc -pthread
NAME =	client
SRC =	engine.c \
	main.c \
	menuManager.c \
	preLoad.c \
	sdlManager.c \
	threadGameEngine.c \
	threadMusic.c 




OBJ = $(SRC:%.c=%.o)
RM = rm -f
CFLAGS =	-Wall -Werror -Wextra

# SDL 2.0 Flags.
SDLFLAGS = `sdl2-config --libs` `sdl2-config --cflags` \
			-lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

all:		$(NAME)

$(NAME):	$(OBJS)
		@echo "> Build BeerBomber"
		@$(CC) $(OBJS) $(CFLAGS) -lpthread -lm $(SDLFLAGS) -o $(NAME)
		@echo "> Done."

clean:
		rm -f $(OBJS)

fclean: 	clean
		rm $(NAME)

re:	fclean all

.PHONY: fclean all clean
