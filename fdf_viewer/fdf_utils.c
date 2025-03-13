#include "fdf.h"

void	reset_img(t_data *data)
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

void	shift_or_zoom(int key, t_matrix *matrix)
{
	if (key == UP)
		matrix->shift_y -= STEPS;
	else if (key == DOWN)
		matrix->shift_y += STEPS;
	else if (key == RIGHT)
		matrix->shift_x += STEPS;
	else if (key == LEFT)
		matrix->shift_x -= STEPS;
	else if (key == ZOOM_IN)
	{
		matrix->zoom += 0.2;
		if (matrix->zoom > MAX_ZOOM)
			matrix->zoom = MAX_ZOOM;
	}
	else if (key == ZOOM_OUT)
	{
		matrix->zoom -= 0.2;
		if (matrix->zoom < MIN_ZOOM)
			matrix->zoom = MIN_ZOOM;
	}
}
