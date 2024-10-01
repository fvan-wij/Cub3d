CC = emcc
CFLAGS = -O3
SRC = ./src
HPATH = ./inc 
LIBFT = ./lib/libft/libft.a
MLX_PATH = ./lib/MLX42/build/
MAUDIO	:= ./lib/miniaudio
MLX_NAME = libmlx42.a
MLX = $(MLX_PATH)$(MLX_NAME)
LINUXFLAGS = -s USE_GLFW=3 -s USE_WEBGL2=1 -s FULL_ES3=1 -s WASM=1 -s NO_EXIT_RUNTIME=1 -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' --preload-file ./data -sALLOW_MEMORY_GROWTH -s TOTAL_STACK=8388608
HEADERS = -I $(HPATH) -I./lib/libft -I ./lib/MLX42/include/MLX42/ -I $(MAUDIO) 

CFILES	= \
		   $(SRC)/main.c 				\
		   $(SRC)/animation.c			\
		   $(SRC)/cbd_main.c			\
		   $(SRC)/cbd_render.c			\
		   $(SRC)/cbd_loop.c			\
		   $(SRC)/beheading.c			\
		   $(SRC)/error.c 		\
		   $(SRC)/entity.c				\
		   $(SRC)/player.c				\
		   $(SRC)/cbd_init.c		\
		   $(SRC)/game_audio.c	\
		   $(SRC)/menu_audio.c	\
		   $(SRC)/cbd_audio.c 	\
		   $(SRC)/miniaudio.c 	\
		   $(SRC)/parser.c 		\
		   $(SRC)/init.c 		\
		   $(SRC)/get_data.c 	\
		   $(SRC)/get_data_bonus.c\
		   $(SRC)/bools.c		\
		   $(SRC)/getters.c		\
		   $(SRC)/validate_data.c \
		   $(SRC)/menu_navigation.c\
		   $(SRC)/menu_setters.c	\
		   $(SRC)/menu_loadmap.c	\
		   $(SRC)/raycaster.c\
		   $(SRC)/vec.c			\
		   $(SRC)/draw.c		\
		   $(SRC)/line.c		\
		   $(SRC)/shape.c		\
		   $(SRC)/color.c		\
		   $(SRC)/post_processing.c \
		   $(SRC)/render_entity.c		\
		   $(SRC)/dithering.c	\
		   $(SRC)/walls.c		\
		   $(SRC)/particles.c	\
		   $(SRC)/gui.c			\
		   $(SRC)/printing.c	\
		   $(SRC)/cleanup.c	\
		   $(SRC)/input.c		\
		   $(SRC)/combat.c		\
		   $(SRC)/player_movement.c		\
		   $(SRC)/player_animation.c		\
		   $(SRC)/particle_movement.c		\
		   $(SRC)/cursor_hook.c		\
		   $(SRC)/mouse_input.c		\
		   $(SRC)/mouse_hook.c		\



OFILES = $(CFILES:.c=.o)
NAME = telestein3d.js

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(OFILES) -o $(NAME) $(LIBFT) $(MLX) $(LINUXFLAGS)

$(SRC)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	rm -rf $(OFILES)
	rm -rf telestein3d.wasm
	rm -rf telestein3d.data

fclean: clean
	rm -f $(NAME)

re: fclean all
