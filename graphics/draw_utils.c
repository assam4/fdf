#include "graphics.h"

void	color_transform(t_bgr *bgr, int *color, int swap_source)
{
	if (swap_source == TO_INT && bgr)
		*color = (bgr->red | (bgr->green << SIZEOF_BYTE)
				| (bgr->blue << SIZEOF_BYTE * 2));
	if (swap_source == TO_BGR && color)
	{
		bgr->blue = (*color >> (SIZEOF_BYTE * 2)) & 0xFF;
		bgr->green = (*color >> SIZEOF_BYTE) & 0xFF;
		bgr->red = *color & 0xFF;
	}
}

static void	change_color(t_point *pixel)
{
	int	color;

	color_transform(&(pixel->color), &color, TO_INT);
	if (pixel->z > START && color == BLUE)
		color = YELLOW;
	else if (pixel->z > START)
		color = BLUE;
	else if (pixel->z == START && color == WHITE)
		color = GREEN;
	else if (pixel->z == START)
		color = WHITE;
	else if (pixel->z < START && color == BORDO)
		color = PURPLE;
	else if (pixel->z < START)
		color = BORDO;
	color_transform(&(pixel->color), &color, TO_BGR);
}

void	set_colors(t_matrix *matrix)
{
	int		y;
	int		x;
	t_point	*pixel;

	y = -1;
	while (++y < matrix->rows)
	{
		x = -1;
		while (++x < matrix->columns)
		{
			pixel = &(matrix->pixels[y][x]);
			change_color(pixel);
		}
	}
}
