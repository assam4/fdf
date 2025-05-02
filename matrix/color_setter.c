#include "matrix.h"

static unsigned int	atohex(const char **line)
{
	unsigned int	result;

	result = START;
	while (**line && ft_strchr(BASE, **line))
	{
		if (**line >= 'a' && **line <= 'f')
			result = result * 16 + (**line - 87);
		if (**line >= 'A' && **line <= 'F')
			result = result * 16 + (**line - 55);
		else
			result = result * 16 + (**line - '0');
		++(*line);
	}
	return (result);
}

void	fd_colors(const char **line, int y, int x, t_matrix *object)
{
	unsigned int	color;

	while (**line == SPACE)
		++(*line);
	if (**line != ',')
		return ;
	object->color_set = SUCCESS;
	++(*line);
	while (**line == SPACE)
		++(*line);
	if (**line == '0' && *(*line + 1) == 'x')
		(*line) += 2;
	color = atohex(line);
	color_transform(&object->pixels[y][x].color, &color, TO_BGR);
}

void	color_transform(t_bgr *bgr, unsigned int *color, int swap_source)
{
	if (swap_source == TO_INT && bgr)
		*color = (bgr->red | (bgr->green << SIZEOF_BYTE)
				| (bgr->blue << SIZEOF_BYTE * TWO));
	if (swap_source == TO_BGR && color)
	{
		bgr->blue = (*color >> (SIZEOF_BYTE * TWO)) & 0xFF;
		bgr->green = (*color >> SIZEOF_BYTE) & 0xFF;
		bgr->red = *color & 0xFF;
	}
}
