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

void	set_color(t_bgr *current, const t_bgr *diff)
{
	current->blue += diff->blue;
	current->green += diff->green;
	current->red += diff->red;
}

int	get_drawline_params(int *distance, int *direction,
			const t_point *start, const t_point *end)
{
	distance[0] = abs(end->x - start->x);
	distance[1] = abs(end->y - start->y);
	distance[2] = distance[(distance[1] > distance[0])];
	direction[0] = 1 - (2 * (start->x >= end->x));
	direction[1] = 1 - (2 * (start->y >= end->y));
	return (distance[0] - distance[1]);
}

t_bgr	get_different(const t_bgr *start, const t_bgr *end, int max_steps)
{
	t_bgr	result;

	result.blue = (end->blue - start->blue) / max_steps;
	result.green = (end->green - start->green) / max_steps;
	result.red = (end->red - start->red) / max_steps;
	return (result);
}
