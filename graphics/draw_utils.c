#include "graphics.h"

void	change_color(t_point *pixel)
{
	if (pixel->color.blue > 255 - 10)
		pixel->color.blue = 255 - pixel->color.blue + 10;
	else
		pixel->color.blue += 10;
	if (pixel->color.green > 255 - 10)
		pixel->color.green = 255 - pixel->color.green + 10;
	else
		pixel->color.green += 10;
	if (pixel->color.red > 255 - 10)
		pixel->color.red = 255 - pixel->color.blue + 10;
	else
		pixel->color.red += 10;
}

void	set_def_colors(t_point *pixel)
{
	unsigned int	color;

	if (pixel->z > START)
		color = COLOR1;
	if (pixel->z == START)
		color = COLOR2;
	else
		color = COLOR3;
	color_transform(&pixel->color, &color, TO_BGR);
}

void	set_colors(t_matrix *matrix, void (*setter)(t_point *))
{
	int		y;
	int		x;
	t_point	*pixel;

	y = LOOP_START;
	while (++y < matrix->rows)
	{
		x = LOOP_START;
		while (++x < matrix->columns)
		{
			pixel = &(matrix->pixels[y][x]);
			setter(pixel);
		}
	}
	matrix->color_set = SUCCESS;
}

void	calc_color(t_bgr *current, const t_bgr *diff)
{
	current->blue += diff->blue;
	current->green += diff->green;
	current->red += diff->red;
}
