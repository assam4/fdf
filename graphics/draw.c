#include "graphics.h"

static void	draw_pixel(t_data *img, t_point *pixel)
{
	int	*location;

	if (img && (pixel->x >= START && pixel->x < WIN_WIDTH)
		&& (pixel->y >= START && pixel->y < WIN_HEIGHT))
	{
		location = (int *)(img->addr
				+ (pixel->y * img->row_len + pixel->x
					* (img->pixel_sizeof / SIZEOF_BYTE)));
		color_transform(&(pixel->color), location, TO_INT);
	}
}

static void	draw_line(t_data *img, t_point current, const t_point *end)
{
	int		distance[3];
	int		shifting[2];
	int		direction[2];
	t_bgr	diff;

	shifting[0] = get_drawline_params(distance, direction, &current, end);
	diff = get_different(&(current.color), &(end->color), distance[2]);
	while (current.x != end->x || current.y != end->y)
	{
		set_color(&(current.color), &diff);
		draw_pixel(img, &current);
		shifting[1] = shifting[0] * 2;
		if (shifting[1] > -distance[1])
		{
			shifting[0] -= distance[1];
			current.x += direction[0];
		}
		if (shifting[1] <= distance[0])
		{
			shifting[0] += distance[0];
			current.y += direction[1];
		}
	}
}

void	draw_matrix(t_data *img)
{
	int			y;
	int			x;
	t_matrix	*object;

	y = START;
	object = img->matrix;
	if (!object || !object->pixels)
		return ;
	while (y < object->rows)
	{
		x = START;
		while (x < object->columns)
		{
			if (x < object->columns - 1)
				draw_line(img, object->pixels[y][x], &object->pixels[y][x + 1]);
			if (y < object->rows - 1)
				draw_line(img, object->pixels[y][x], &object->pixels[y + 1][x]);
			++x;
		}
		++y;
	}
}
