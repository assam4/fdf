#include "graphics.h"

void	to_isometric(t_matrix *matrix)
{
	int	y;
	int	x;
	int	iso_x;
	int	iso_y;

	y = -1;
	while (++y < matrix->rows)
	{
		x = -1;
		while (++x < matrix->columns)
		{
			iso_x = (x - y) * cos(ANGLE_30) * (SPACING * matrix->zoom / 2);
			iso_y = (x + y) * sin(ANGLE_30) * (SPACING * matrix->zoom / 2)
				- (matrix->pixels[y][x].z * matrix->zscale);
			matrix->pixels[y][x].x = WIN_WIDTH / 2 + iso_x
				- ((matrix->columns - 1) * SPACING / 2) + matrix->shift_x;
			matrix->pixels[y][x].y = WIN_HEIGHT / 2 + iso_y
				- ((matrix->rows - 1) * SPACING / 2) + matrix->shift_y;
		}
	}
}

void	draw_matrix(t_data *img, void (*transform)(t_matrix *m))
{
	int			x;
	int			y;
	t_matrix	*matrix;

	matrix = img->matrix;
	transform(matrix);
	y = -1;
	while (++y < matrix->rows)
	{
		x = -1;
		while (++x < matrix->columns)
		{
			if (x < matrix->columns - 1)
				draw_line(img, matrix->pixels[y][x],
					&(matrix->pixels[y][x + 1]));
			if (y < matrix->rows - 1)
				draw_line(img, matrix->pixels[y][x],
					&(matrix->pixels[y + 1][x]));
		}
	}
}
