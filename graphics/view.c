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
	int	per[2];
	int	map_center[2];

	y = LOOP_START;
	while (++y < matrix->rows)
	{
		x = LOOP_START;
		while (++x < matrix->columns)
		{
			per[1] = set_perspective(&per[0], x, y, matrix);
			map_center[0] = (matrix->columns - 1) * matrix->zoom / 2;
			map_center[1] = (matrix->rows - 1) * matrix->zoom / 2;
			matrix->pixels[y][x].x = WIN_WIDTH / 2 + per[0]
				+ matrix->shift_x - map_center[0];
			matrix->pixels[y][x].y = WIN_HEIGHT / 2 + per[1]
				+ matrix->shift_y - map_center[1];
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
		* (SPACING * matrix->zoom / 2);
	iso_y = (temp_x + temp_y) * sin(ANGLE_30)
		* (SPACING * matrix->zoom / 2)
		- (temp_z * (matrix->zscale));
	return (iso_y);
}

void	to_isometric(t_matrix *matrix)
{
	int	y;
	int	x;
	int	iso[2];
	int	map_center[2];

	y = LOOP_START;
	while (++y < matrix->rows)
	{
		x = LOOP_START;
		while (++x < matrix->columns)
		{
			iso[1] = set_isometric(&iso[0], x, y, matrix);
			map_center[0] = (matrix->columns - 1) * SPACING * matrix->zoom / 2;
			map_center[1] = (matrix->rows - 1) * SPACING * matrix->zoom / 2;
			matrix->pixels[y][x].x = WIN_WIDTH / 2 + iso[0]
				+ matrix->shift_x - map_center[0];
			matrix->pixels[y][x].y = WIN_HEIGHT / 2 + iso[1]
				+ matrix->shift_y - map_center[1];
		}
	}
}
