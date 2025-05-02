#include "fdf.h"

static bool	check_42filename(const char *filename)
{
	char	*format;

	format = ft_strchr(filename, FORMAT_START);
	if (format && ft_strncmp(format, FILE_FORMAT,
			ft_strlen(FILE_FORMAT) + 1) == IS_EQUAL)
		return (true);
	else
		return (false);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc == 2 && check_42filename(argv[1]))
	{
		data = ft_calloc(1, sizeof(t_data));
		if (data)
		{
			data->matrix = get_matrix(argv[1]);
			if (!data->matrix)
				return (free(data), ALLOCATION_ERROR);
			run_fdf(data);
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
