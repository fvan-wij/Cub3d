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
	ERR_ALLOC,
	ERR_INVALID_MAP,
	ERR_INVALID_WALL,
	ERR_INVALID_START,
	ERR_FILE_INEXISTS,
	ERR_TEX_SIZE,
	ERR_UNKNOWN_ELEM,
	ERR_LOAD_MAP,
	ERR_MAPCONTENT_SEQUENCE,
	ERR_SIZE,
} e_err;

int		cbd_error(e_err err_msg);
bool	arg_is_valid(int argc, char *argv[]);
bool	extension_is_valid(char *file);

#endif
