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
			printf("%i __ %i \n", matrix->pixels[y][x].y, matrix->pixels[y][x].x);
			++x;
		}
		++y;
	}
}

static void	update_view(t_data *data)
{
	if (data->img)
		mlx_destroy_image(data->mlx_connect, data->img);
	data->img = mlx_new_image(data->mlx_connect, WIN_WIDTH, WIN_HEIGHT);
	draw_matrix(data);
	mlx_put_image_to_window(data->mlx_connect, data->window
				, data->img, START, START);
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
	update_view(data);
	return (SUCCESS);
}
