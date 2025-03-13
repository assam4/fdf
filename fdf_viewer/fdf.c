#include "fdf.h"

t_matrix	*get_matrix(const char *fname)
{
	t_matrix	*matrix;
	int			fd;
	int			status;

	matrix = ft_calloc(1, sizeof(t_matrix));
	if (!matrix)
		return (NULL);
	fd = open(fname, O_RDONLY);
	if (fd == -1)
		return (free(matrix), NULL);
	status = file_format_checking(fd, &(matrix->columns), &(matrix->rows));
	close(fd);
	if (status != SUCCESS)
		return (free(matrix), NULL);
	fd = open(fname, O_RDONLY);
	if (fd == -1)
		return (free(matrix), NULL);
	status = initialize_matrix(fd, &matrix);
	close(fd);
	if (status != SUCCESS)
		return (free(matrix), NULL);
	set_zoom(matrix, WIN_WIDTH, WIN_HEIGHT, SPACING);
	set_zscale(matrix, WIN_HEIGHT);
	set_colors(matrix);
	return (matrix);
}

static void	set_win_config(t_data *data)
{
	data->mlx_connect = mlx_init();
	data->window = mlx_new_window(data->mlx_connect,
			WIN_WIDTH, WIN_HEIGHT, TITLE);
	data->img = mlx_new_image(data->mlx_connect, WIN_WIDTH, WIN_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &(data->pixel_sizeof),
			&(data->row_len), &(data->endian));
}

static int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx_connect, data->window);
	mlx_destroy_image(data->mlx_connect, data->img);
	deallocate_matrix(&(data->matrix));
	free(data);
	exit(0);
	return (0);
}

static int	key_event(int key, void *object)
{
	t_data	*data;

	data = (t_data *)object;
	if (key == ESC)
		return (close_window(data));
	if ((key >= LEFT && key <= DOWN) || key == ZOOM_IN || key == ZOOM_OUT)
		shift_or_zoom(key, data->matrix);
	else if (key == 'c')
		set_colors(data->matrix);
	reset_img(data);
	draw_matrix(data, to_isometric);
	mlx_put_image_to_window(data->mlx_connect, data->window,
		data->img, START, START);
	return (SUCCESS);
}

void	run_fdf(t_data *data)
{
	set_win_config(data);
	draw_matrix(data, to_isometric);
	mlx_put_image_to_window(data->mlx_connect, data->window,
		data->img, START, START);
	mlx_hook(data->window, 2, 1L << 0, key_event, data);
	mlx_hook(data->window, 17, 0, close_window, data);
	mlx_loop(data->mlx_connect);
}
