#include "graphics.h"

void	color_transform(t_bgr *bgr, int *color, int swap_source)
{
	if (swap_source == TO_INT && bgr)
		*color = (bgr->red | (bgr->green << SIZEOF_BYTE)
				| (bgr->blue << SIZEOF_BYTE * 2));
	if (swap_source == TO_BGR && color)
	{
		bgr->red = (*color >> (SIZEOF_BYTE * 2)) & 0xFF;
		bgr->green = (*color >> SIZEOF_BYTE) & 0xFF;
		bgr->blue = *color & 0xFF;
	}
}

static void	set_color(t_bgr *start_color, const t_bgr *delta_color
			, int *distance, int shifting)
{
	float	coefficient;

	coefficient = (float)(shifting) / (distance[0] + distance[1]);
	if (start_color->blue < delta_color->blue)
		start_color->blue += (int)(delta_color->blue * coefficient);
	else
		start_color->blue -= (int)(delta_color->blue * coefficient);
	if (start_color->green < delta_color->green)
		start_color->green += (int)(delta_color->green * coefficient);
	else
		start_color->green -= (int)(delta_color->green * coefficient);
	if (start_color->red < delta_color->red)
		start_color->red += (int)(delta_color->red * coefficient);
	else
		start_color->red -= (int)(delta_color->red * coefficient);
}

static void	draw_pixel(t_image *img, t_point *pixel)
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

static void	draw_line(t_image *img, t_point one, const t_point *second)
{
	int		distance[2];
	int		shifting[2];
	int		direction[2];

	distance[0] = abs(second->x - one.x);
	distance[1] = abs(second->y - one.y);
	direction[0] = 1 - (2 * (one.x >= second->x));
	direction[1] = 1 - (2 * (one.y >= second->y));
	shifting[0] = distance[0] - distance[1];
	while (one.x != second->x || one.y != second->y)
	{
		set_color(&(one.color), &(second->color), distance, shifting[0]);
		draw_pixel(img, &one);
		shifting[1] = shifting[0] * 2;
		if (shifting[1] > -distance[1])
		{
			shifting[0] -= distance[1];
			one.x += direction[0];
		}
		if (shifting[1] <= distance[0])
		{
			shifting[0] += distance[0];
			one.y += direction[1];
		}
	}
}

void	draw_matrix(t_image *img, t_matrix *object)
{
	int	y;
	int	x;

	y = START;
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
