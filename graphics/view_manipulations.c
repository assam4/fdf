#include "graphics.h"

static void	shifting_matrix(t_matrix *matrix, int col_shift, int row_shift)
{
	int	y;
	int	x;

	y = START;
	while (y < matrix->rows)
	{
		x = START;
		while (x < matrix->columns)
		{
			matrix->pixels[y][x].y += row_shift;
			matrix->pixels[y][x].x += col_shift;
			++x;
		}
		++y;
	}
}

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
		shifting_matrix(data->matrix, UNCHANGE, -(STEPS));
	else if (key == DOWN)
		shifting_matrix(data->matrix, UNCHANGE, STEPS);
	else if (key == RIGHT)
		shifting_matrix(data->matrix, STEPS, UNCHANGE);
	else if (key == LEFT)
		shifting_matrix(data->matrix, -(STEPS), UNCHANGE);
	reset_img(data);
	draw_matrix(data);
	mlx_put_image_to_window(data->mlx_connect, data->window,
			data->img, START, START);
	return (SUCCESS);
}
