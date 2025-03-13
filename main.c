#include "fdf.h"

int main(int argc, char **argv)
{
    t_data	*data;

    data = ft_calloc(1, sizeof(t_data));
    if (argc == 2 && data)
    {
	    data->matrix = get_matrix(argv[1]);
	    if (!data->matrix)
		    return (free(data), 1);
	    run_fdf(data);
    }
    return (0);
}
