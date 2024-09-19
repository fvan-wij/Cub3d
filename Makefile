NAME    := telestein3d.exe
CFLAGS  := -Wextra -Wall -Wunreachable-code -O2
CC      := x86_64-w64-mingw32-gcc

LIBMLX  := ./lib/MLX42
LIBFT   := ./lib/libft
MAUDIO  := ./lib/miniaudio
LIBGLFW := /home/flip/Cub3d_Telestein3D/lib

# Update library paths and linker flags
LIBS    := $(LIBMLX)/build/libmlx42.a $(LIBGLFW)/libglfw3.a $(LIBFT)/libft.a -lopengl32 -lpthread
LDFLAGS := -static -L$(LIBGLFW)
HEADERS := -I ./inc -I $(LIBMLX)/include/MLX42 -I $(LIBFT) -I $(MAUDIO)

# List of source files and corresponding object files
SRCS    := \
           main.c 				\
           animation.c			\
           cbd_main.c			\
           cbd_render.c			\
           cbd_loop.c			\
           beheading.c			\
           error.c 		\
           entity.c				\
           player.c				\
           cbd_init.c		\
           game_audio.c	\
           menu_audio.c	\
           cbd_audio.c 	\
           miniaudio.c 	\
           parser.c 		\
           init.c 		\
           get_data.c 	\
           get_data_bonus.c\
           bools.c		\
           getters.c		\
           validate_data.c \
           menu_navigation.c\
           menu_setters.c	\
           menu_loadmap.c	\
           raycaster.c\
           vec.c			\
           draw.c		\
           line.c		\
           shape.c		\
           color.c		\
           post_processing.c \
           entity.c		\
           dithering.c	\
           walls.c		\
           particles.c	\
           gui.c			\
           printing.c	\
           cleanup.c	\
           input.c		\
           combat.c		\
           player_movement.c		\
           player_animation.c		\
           particle_movement.c		\
           cursor_hook.c		\
           mouse_input.c		\
           mouse_hook.c		\

SRCDIR  := ./src
OBJDIR  := ./obj
OBJS    := $(SRCS:%.c=$(OBJDIR)/%.o)

all: init-submodules libft libmlx $(NAME)

run: all
	./$(NAME)

init-submodules:
	git submodule update --init --recursive

libmlx:
	@cp -f ./data/default.frag ./lib/MLX42/shaders/default.frag
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -s -C $(LIBMLX)/build -j2

libft:
	@make -s -C $(LIBFT)

# Rule to compile .c files to .o files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ && printf "[Cub3d]\033[0;32m\033[1m Building: $(notdir $<) \033[0m\n"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(HEADERS) $(LIBS) $(LDFLAGS) -o $(NAME)
	@printf "[Cub3d]\033[0;32m\033[1m Compiled successfully ✅\033[0m\n"
	@printf "[Cub3d]\033[0;32m\033[1m Run the telestein3d executable './$(NAME)' to get started.\033[0m\n"

clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(LIBMLX)/build
	@make -s -C $(LIBFT) clean
	@echo $(Yellow) Cleaned object files! $(Text_Off)

fclean: clean
	@rm -rf $(NAME)
	@make -s -C $(LIBFT) fclean
	@echo $(Yellow) Cleaned executable! $(Text_Off)

re: clean all

.PHONY: all clean fclean re libmlx
