#include <cub3d.h>
#include <cbd_parser.h>
#include <cbd_error.h>
#include <libft.h>


int32_t	main(int argc, char *argv[])
{
	t_app cub3d;

	if (!arg_is_valid(argc, argv))
		return (FAILURE);
	ft_memset(&cub3d, 0, sizeof(t_app));
	if (!cbd_parse_map(argv[1], &cub3d))
		return (FAILURE);

	return (SUCCESS);
}
