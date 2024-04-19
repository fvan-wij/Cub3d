NAME	:= cub3d
# CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
CFLAGS	:= -Wextra -Wall -Wunreachable-code -O2
LIBMLX	:= ./lib/MLX42
LIBFT	:= ./lib/libft
MAUDIO	:= ./lib/miniaudio

HEADERS	:= -I ./inc -I $(LIBMLX)/include/MLX42 -I $(LIBFT) -I $(MAUDIO)
LIBS	:= $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a -ldl -lglfw -lpthread -lm
SRCS	:= \
		   main.c 				\
		   animation.c			\
		   cbd_main.c			\
		   cbd_render.c			\
		   cbd_loop.c			\
		   beheading.c			\
		   error/error.c 		\
		   entity.c				\
		   player.c				\
		   init/cbd_init.c		\
		   audio/game_audio.c	\
		   audio/menu_audio.c	\
		   audio/cbd_audio.c 	\
		   audio/miniaudio.c 	\
		   parser/parser.c 		\
		   parser/init.c 		\
		   parser/get_data.c 	\
		   parser/get_data_bonus.c\
		   parser/bools_cub.c	\
		   parser/bools_map.c	\
		   parser/getters.c		\
		   parser/validate_data.c \
		   parser/bools_validate.c\
		   menu/menu_navigation.c\
		   menu/menu_setters.c	\
		   menu/menu_loadmap.c	\
		   raycaster/raycaster.c\
		   vec/vec.c			\
		   render/draw.c		\
		   render/line.c		\
		   render/shape.c		\
		   render/color.c		\
		   render/post_processing.c \
		   render/entity.c		\
		   render/dithering.c	\
		   render/walls.c		\
		   render/particles.c	\
		   utility/printing.c	\
		   utility/cleanup.c	\
		   input/input.c		\
		   input/combat.c		\
		   input/player_movement.c		\
		   input/player_animation.c		\
		   input/particle_movement.c		\
		   input/cursor_hook.c		\
		   input/mouse_input.c		\
		   input/mouse_hook.c		\

SRCDIR	:= ./src
OBJDIR	:= ./obj
OBJS	:= $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))
SRCS	:= $(addprefix $(SRCDIR)/,$(SRCS))

ifdef DEBUG
	CC += -g -fsanitize=address
	LIBFT_DEBUG += DEBUG=1
endif

ifdef OPTIMIZE
	CFLAGS += -Ofast
endif

all: libft libmlx $(NAME)

run: all

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -s -C $(LIBMLX)/build -j4

libft:
	@make -s $(LIBFT_DEBUG) -C $(LIBFT)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<  && printf "[Cub3d]\033[0;32m\033[1m Building: $(notdir $<) \033[0m\n"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@printf "[Cub3d]\033[0;32m\033[1m Compiled succesfully ✅\033[0m\n"
	@printf "[Cub3d]\033[0;32m\033[1m Run the cub3d executable to get started.\033[0m\n"

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

.PHONY: all, clean, fclean, re, libmlx

# Colors #############################################
Black		= "\033[0;30m"		# Black
Red			= "\033[0;31m"		# Red
Green		= "\033[0;32m"		# Green
Yellow		= "\033[0;33m"		# Yellow
Blue		= "\033[0;34m"		# Blue
Purple		= "\033[0;35m"		# Purple
Cyan		= "\033[0;36m"		# Cyan
White		= "\033[0;37m"		# White
Text_Off	= "\033[0m"			# Text Style Off
Bold		= "\033[1m"			# Text Style Bold
######################################################
