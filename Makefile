NAME	:= cub3d
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX	:= ./lib/MLX42
LIBFT	:= ./lib/libft

HEADERS	:= -I ./inc -I $(LIBMLX)/include/MLX42 -I $(LIBFT)
LIBS	:= $(LIBMLX)/build/libmlx42.a $(LIBFT)/libft.a -ldl -lglfw -pthread -lm 
SRCS	:= \
		   main.c 				\
		   error/error.c 		\
		   parser/parser.c 		\
		   parser/init.c 		\
		   parser/textures.c 	\

SRCDIR	:= ./src
OBJDIR	:= ./obj
OBJS	:= $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))
SRCS	:= $(addprefix $(SRCDIR)/,$(SRCS))

ifdef DEBUG
	CC += -g -fsanitize=address
	LIBFT_DEBUG += DEBUG=1
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

