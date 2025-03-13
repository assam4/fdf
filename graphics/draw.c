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

static int	get_drawline_params(int *distance, int *direction,
			const t_point *start, const t_point *end)
{
	distance[ZERO] = abs(end->x - start->x);
	distance[ONE] = abs(end->y - start->y);
	distance[TWO] = distance[(distance[ONE] > distance[ZERO])];
	direction[ZERO] = ONE - (TWO * (start->x >= end->x));
	direction[ONE] = ONE - (TWO * (start->y >= end->y));
	return (distance[ZERO] - distance[ONE]);
}

static t_bgr	get_different(const t_bgr *start, const t_bgr *end
			, int max_steps)
{
	t_bgr	result;

	if (max_steps == START)
	{
		result.blue = end->blue - start->blue;
		result.green = end->green - start->green;
		result.red = end->red - start->red;
	}
	else
	{
		result.blue = (end->blue - start->blue) / max_steps;
		result.green = (end->green - start->green) / max_steps;
		result.red = (end->red - start->red) / max_steps;
	}
	return (result);
}

static void	draw_line(t_data *img, t_point current, const t_point *end)
{
	int		distance[THREE];
	int		shifting[TWO];
	int		direction[TWO];
	t_bgr	diff;

	shifting[ZERO] = get_drawline_params(distance, direction, &current, end);
	diff = get_different(&(current.color), &(end->color), distance[TWO]);
	while (current.x != end->x || current.y != end->y)
	{
		calc_color(&(current.color), &diff);
		draw_pixel(img, &current);
		shifting[ONE] = shifting[ZERO] * TWO;
		if (shifting[ONE] > -distance[ONE])
		{
			shifting[ZERO] -= distance[ONE];
			current.x += direction[ZERO];
		}
		if (shifting[ONE] <= distance[ZERO])
		{
			shifting[ZERO] += distance[ZERO];
			current.y += direction[ONE];
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
	y = LOOP_START;
	while (++y < matrix->rows)
	{
		x = LOOP_START;
		while (++x < matrix->columns)
		{
			if (x < matrix->columns - ONE)
				draw_line(img, matrix->pixels[y][x],
					&(matrix->pixels[y][x + ONE]));
			if (y < matrix->rows - ONE)
				draw_line(img, matrix->pixels[y][x],
					&(matrix->pixels[y + ONE][x]));
		}
	}
}
