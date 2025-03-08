#include "graphics.h"

static t_matrix	*get_matrix(const char *fname)
{
	t_matrix	*matrix;
	int		fd;
	int		status;

	matrix = ft_calloc(1, sizeof(t_matrix));
	if (!matrix)
		return (NULL);
	fd = open(fname, O_RDONLY);
	if (fd == -1)
		return (free(matrix), NULL);
	status = file_format_checking(fd, &(matrix->columns), &(matrix->rows));
	close(fd);
	if (status == SUCCESS)
	{
		printf("ROWS: %i\n COLUMNS: %i\n", matrix->rows, matrix->columns);
		fd = open(fname, O_RDONLY);
		if (fd == -1)
			return (free(matrix), NULL);
		status = initialize_matrix(fd, matrix);
		close(fd);
		if (status != SUCCESS)
			return (free(matrix), NULL);
		set_iso_matrix(matrix);
		return (matrix);
	}
	return (NULL);
}

static void	set_win_config(t_data *data)
{
	data->mlx_connect = mlx_init();
	data->window = mlx_new_window(data->mlx_connect, WIN_WIDTH, WIN_HEIGHT, TITLE);
	data->img = mlx_new_image(data->mlx_connect, WIN_WIDTH, WIN_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &(data->pixel_sizeof),
				&(data->row_len), &(data->endian));
}

int main(int argc, char **argv)
{
    t_data	*data;

    data = ft_calloc(1, sizeof(t_data));
    if (argc == 2 && data)
    {
	    data->matrix = get_matrix(argv[1]);
	    if (!data->matrix)
		    return (free(data), 1);
	    set_win_config(data);
    	draw_matrix(data);
	printf("DONE\n");
	mlx_put_image_to_window(data->mlx_connect, data->window, data->img, START, START);
	mlx_hook(data->window, 2, 1L << 0, key_event, data);
	mlx_loop(data->mlx_connect);
	deallocate_matrix(&(data->matrix));
	free(data);
    }
    return (0);
}
