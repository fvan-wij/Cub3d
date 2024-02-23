#include <libft.h>
#include <cbd_error.h>
#include <unistd.h>

static const char* g_error[ERR_SIZE + 1] =
{
	[INVALID_ARGC] = "Cub3d Error: invalid amount of arguments",
	[INVALID_EXTENSION] = "Cub3d Error: invalid file extension. Program only accepts .cub files",
	[ERR_OPEN] = "Cub3d Error: could not open file",
	[ERR_ALLOC] = "Cub3d Error: error allocating memory",
	[ERR_INVALID_MAP] = "Cub3d Error: map is invalid",
	[ERR_SIZE] = "n/a",
};

int	cbd_error(e_err err_msg) 
{
	ft_putstr_fd_nl(g_error[err_msg], STDERR_FILENO);
	return (err_msg);
}

bool	extension_is_valid(char *file)
{
	int len;

	if (!file)
		return (false);
	len = ft_strlen(file);
	if (len > 4 && ft_strncmp(&file[len - 4], ".cub", 4) == 0)
		return (true);
	else
		return (false);
}

bool	arg_is_valid(int argc, char *argv[])
{
	if (argc != 2)
		return (cbd_error(INVALID_ARGC), false);
	if (!extension_is_valid(argv[1]))
		return (cbd_error(INVALID_EXTENSION), false);
	return (true);
}
