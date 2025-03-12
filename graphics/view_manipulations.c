#include "graphics.h"

static void	reset_img(t_data *data)
{
	int	y;
	int	x;
	int	*location;

	y = START;
	while (y < WIN_HEIGHT)
	{
		x = START;
		while (x < WIN_WIDTH)
		{
			location = (int *)(data->addr
					+ (y * data->row_len + x
						* (data->pixel_sizeof / SIZEOF_BYTE)));
			*location = BLACK;
			++x;
		}
		++y;
	}
}

int	key_event(int key, void *object)
{
	t_data	*data;

	data = (t_data *)object;
	if (key == ESC)
	{
		mlx_destroy_window(data->mlx_connect, data->window);
		exit(SUCCESS);
	}
	else if (key == UP)
		data->matrix->shift_y -= STEPS;
	else if (key == DOWN)
		data->matrix->shift_y += STEPS;
	else if (key == RIGHT)
		data->matrix->shift_x += STEPS;
	else if (key == LEFT)
		data->matrix->shift_x -= STEPS;
	else if (key == ZOOM_IN)
	{
		data->matrix->zoom += 0.2;
		if (data->matrix->zoom > MAX_ZOOM)
			data->matrix->zoom = MAX_ZOOM;
	}
	else if (key == ZOOM_OUT)
	{
		data->matrix->zoom -= 0.2;
		if (data->matrix->zoom < MIN_ZOOM)
			data->matrix->zoom = MIN_ZOOM;
	}
	else if (key == 'c')
		set_colors(data->matrix);
	reset_img(data);
	draw_matrix(data, to_isometric);
	mlx_put_image_to_window(data->mlx_connect, data->window,
			data->img, START, START);
	return (SUCCESS);
}
