#include "graphics.h"

static void	rotate(float angle, float *a, float *b, char flag)
{
	float	temp_a;
	float	temp_b;

	temp_a = *a;
	temp_b = *b;
	if (flag == ROTATE_X)
	{
		*a = temp_a;
		*b = temp_a * sin(angle) + temp_b * cos(angle);
	}
	else if (flag == ROTATE_Y)
	{
		*a = temp_a * cos(angle) + temp_b * sin(angle);
		*b = -temp_a * sin(angle) + temp_b * cos(angle);
	}
	else if (flag == ROTATE_Z)
	{
		*a = temp_a * cos(angle) - temp_b * sin(angle);
		*b = temp_a * sin(angle) + temp_b * cos(angle);
	}
}

static int	set_perspective(int *per_x, int x, int y, const t_matrix *matrix)
{
	float	temp_x;
	float	temp_y;
	float	temp_z;
	float	divisor;

	temp_x = x * matrix->zoom;
	temp_y = y * matrix->zoom;
	temp_z = matrix->pixels[y][x].z;
	rotate(matrix->rotate_x, &temp_y, &temp_z, ROTATE_X);
	rotate(matrix->rotate_y, &temp_x, &temp_z, ROTATE_Y);
	rotate(matrix->rotate_z, &temp_x, &temp_y, ROTATE_Z);
	divisor = (temp_z + CAMERA_DISTANCE);
	if (divisor == START)
		divisor = MIN_DIVISOR;
	*per_x = (temp_x * FOCAL_LENGTH) / divisor;
	return ((temp_y * FOCAL_LENGTH) / divisor
		- (temp_z * matrix->zscale));
}

void	to_perspective(t_matrix *matrix)
{
	int	y;
	int	x;
	int	per_x;
	int	per_y;

	y = LOOP_START;
	while (++y < matrix->rows)
	{
		x = LOOP_START;
		while (++x < matrix->columns)
		{
			per_y = set_perspective(&per_x, x, y, matrix);
			matrix->pixels[y][x].x = WIN_WIDTH / TWO
				+ per_x + matrix->shift_x;
			matrix->pixels[y][x].y = WIN_HEIGHT / TWO
				+ per_y + matrix->shift_y;
		}
	}
}

static int	set_isometric(int *iso_x, int x, int y, const t_matrix *matrix)
{
	float	temp_x;
	float	temp_y;
	float	temp_z;
	int		iso_y;

	temp_x = x;
	temp_y = y;
	temp_z = matrix->pixels[y][x].z;
	rotate(matrix->rotate_x, &temp_y, &temp_z, ROTATE_X);
	rotate(matrix->rotate_y, &temp_x, &temp_z, ROTATE_Y);
	rotate(matrix->rotate_z, &temp_x, &temp_y, ROTATE_Z);
	*iso_x = (temp_x - temp_y) * cos(ANGLE_30)
		* (SPACING * matrix->zoom / TWO);
	iso_y = (temp_x + temp_y) * sin(ANGLE_30)
		* (SPACING * matrix->zoom / TWO)
		- (temp_z * (matrix->zscale));
	return (iso_y);
}

void	to_isometric(t_matrix *matrix)
{
	int	y;
	int	x;
	int	iso_x;
	int	iso_y;

	y = LOOP_START;
	while (++y < matrix->rows)
	{
		x = LOOP_START;
		while (++x < matrix->columns)
		{
			iso_y = set_isometric(&iso_x, x, y, matrix);
			matrix->pixels[y][x].x = WIN_WIDTH / TWO + iso_x
				- ((matrix->columns - ONE) * SPACING / TWO) + matrix->shift_x;
			matrix->pixels[y][x].y = WIN_HEIGHT / TWO + iso_y
				- ((matrix->rows - ONE) * SPACING / TWO) + matrix->shift_y;
		}
	}
}
