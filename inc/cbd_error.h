#ifndef CBD_ERROR_H
# define CBD_ERROR_H

# include <libft.h>
# include <stdbool.h>
# define SUCCESS 0
# define FAILURE 1

typedef enum e_err {
	INVALID_ARGC,
	INVALID_EXTENSION,
	ERR_OPEN,
	ERR_SIZE,
} e_err;

int		cbd_error(e_err err_msg);
bool	arg_is_valid(int argc, char *argv[]);
bool	extension_is_valid(char *file);

#endif
