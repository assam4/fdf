#include "fdf.h"

static int	check_42filename(const char *filename)
{
	char	*format;

	format = ft_strchr(filename, FORMAT_START);
	if (format && ft_strncmp(format, FILE_FORMAT, FOUR) == IS_EQUAL)
		return (SUCCESS);
	else
		return (VALIDATION_ERROR);
}

int main(int argc, char **argv)
{
    t_data	*data;

    if (argc == TWO && check_42filename(argv[ONE]) == SUCCESS)
    {
	    data = ft_calloc(ONE, sizeof(t_data));
	    if (data)
	    {
		    data->matrix = get_matrix(argv[ONE]);
		    if (!data->matrix)
			    return (free(data), ALLOCATION_ERROR);
		    run_fdf(data);
	    }
    }
    return (SUCCESS_EXIT);
}
