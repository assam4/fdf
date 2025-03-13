#include "graphics.h"

static void	rotate(float angle, float *a, float *b, char flag)
{
	float	temp_a;
	float	temp_b;


	temp_a = *a;
	temp_b = *b;
	if (flag == 'x') 
	{
		*a = temp_a;
		*b = temp_a * sin(angle) + temp_b * cos(angle);
	}
	else if (flag == 'y')
	{
		*a = temp_a * cos(angle) + temp_b * sin(angle);
		*b = -temp_a * sin(angle) + temp_b * cos(angle);
	}
	else if (flag == 'z')
	{
		*a = temp_a * cos(angle) - temp_b * sin(angle);
		*b = temp_a * sin(angle) + temp_b * cos(angle);
	}
}

static int	set_iso(int *iso_x, int x, int y, const t_matrix *matrix)
{
	float	temp_x;
	float	temp_y;
	float	temp_z;
	int	iso_y;

	temp_x = x;
	temp_y = y;
	temp_z = matrix->pixels[y][x].z;
	rotate(matrix->rotate_x, &temp_y, &temp_z, 'x');
	rotate(matrix->rotate_y, &temp_x, &temp_z, 'y');
	rotate(matrix->rotate_z, &temp_x, &temp_y, 'z');
	*iso_x = (temp_x - temp_y) * cos(ANGLE_30) * (SPACING * matrix->zoom / 2);
	iso_y = (temp_x + temp_y) * sin(ANGLE_30) * (SPACING * matrix->zoom / 2)
		- (temp_z * (matrix->zscale));
	return (iso_y);
}

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
			iso_y = set_iso(&iso_x, x, y, matrix);
		//	iso_x = (x - y) * cos(ANGLE_30) * (SPACING * matrix->zoom / 2);
		//	iso_y = (x + y) * sin(ANGLE_30) * (SPACING * matrix->zoom / 2)
		//		- (matrix->pixels[y][x].z * matrix->zscale);
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
