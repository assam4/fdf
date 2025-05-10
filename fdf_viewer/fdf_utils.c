#include "fdf.h"

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
		matrix->zoom += ZOOM_STEP;
		if (matrix->zoom > MAX_ZOOM)
			matrix->zoom = MAX_ZOOM;
	}
	else if (key == ZOOM_OUT)
	{
		matrix->zoom -= ZOOM_STEP;
		if (matrix->zoom < MIN_ZOOM)
			matrix->zoom = MIN_ZOOM;
	}
}

void	rotate(int key, t_matrix *matrix)
{
	if (key == ROTATE_X)
	{
		matrix->rotate_x += ROTATE_STEP;
		if (matrix->rotate_x == ANGLE_360)
			matrix->rotate_x = START;
	}
	else if (key == ROTATE_Y)
	{
		matrix->rotate_y += ROTATE_STEP;
		if (matrix->rotate_y == ANGLE_360)
			matrix->rotate_y = START;
	}
	else if (key == ROTATE_Z)
	{
		matrix->rotate_z += ROTATE_STEP;
		if (matrix->rotate_z == ANGLE_360)
			matrix->rotate_z = START;
	}
}

int	update_window(t_data *data)
{
	if (data->is_changed)
	{
		ft_bzero(data->addr, data->row_len * WIN_HEIGHT);
		draw_matrix(data, data->projection);
		mlx_put_image_to_window(data->mlx_connect, data->window,
			data->img, START, START);
		data->is_changed = START;
	}
	return (EXIT_SUCCESS);
}
