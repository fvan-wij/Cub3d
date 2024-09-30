NAME		:=	libft.a

HEADER		:=	libft.h

SRC			:=	ft_arrlen.c \
			ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_iswhitespace.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_strchr.c \
			ft_strchr_index.c \
			ft_strdup.c \
			ft_strcpy.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_putstr_fd_nl.c \
			ft_putstr_fd_2d.c \
			ft_itoa.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_split.c \
			ft_striteri.c \
			ft_strmapi.c \
			ft_lstnew_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstsize_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstmap_bonus.c \
			\
			get_next_line.c \
			\
			ft_printf.c \
			ft_printspecifier.c \
			ft_put_cap_hex.c \
			ft_put_ui_nbr.c \
			ft_putadr.c \
			ft_putchar.c \
			ft_puthex.c \
			ft_putnbr.c \
			ft_putstr.c \
			\
			ft_strjoin_and_free.c \
			ft_split_nl.c \
			ft_atoh.c \
			ft_word_counter_quotations.c \
			ft_split_quotations.c \
			ft_find_envp_path_index.c \
			ft_del_2d.c \
			ft_strisalpha.c \
			ft_copy_double_array.c \
			ft_add_2d.c \
			ft_replace_str_in_array.c \
			ft_remove_str_from_array.c \
			ft_inject_str_in_array.c \
			ft_wordcount.c \
			ft_containschar.c \
			ft_rev_free_2d.c \

CC			:= emcc


			
# Regular Colors #############################################
Black		= "\033[0;30m"		# Black
Red			= "\033[0;31m"		# Red
Green		= "\033[0;32m"		# Green
Yellow		= "\033[0;33m"		# Yellow
Blue		= "\033[0;34m"		# Blue
Purple		= "\033[0;35m"		# Purple
Cyan		= "\033[0;36m"		# Cyan
White		= "\033[0;37m"		# White
# Text styles
Bold		= "\033[1m"
# Reset
Text_Off	= "\033[0m"			# Text Style
#############################################################

OBJ 		:= $(SRC:.c=.o)

COMPILER	:= cc

CFLAGS		:= -Wall -Werror -Wextra

RMV			:= rm -f

ifdef DEBUG
	COMPILER += -g
endif

all: 		$(NAME)

$(NAME): 	$(OBJ)
	@ar -rcs $(NAME) $(OBJ)

%.o: 		%.c
			@echo $(Cyan) Building... [$<] $(Text_Off)
			@$(CC) $(CFLAGS) -c -o $@ $^

clean: 		
			@$(RMV) $(OBJ)

fclean: 	clean
			@$(RMV) $(NAME)

re: 		fclean $(NAME)

.PHONY:		all clean fclean re bonus
