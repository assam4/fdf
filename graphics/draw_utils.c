/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 22:08:07 by saslanya          #+#    #+#             */
/*   Updated: 2025/03/04 22:11:36 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_bgr	int_to_bgr(int color)
{
	t_bgr	bgr;

	bgr.blue = color & 0xFF;
	bgr.green = (color >> 8) & 0xFF;
	bgr.red = (color >> 16) & 0xFF;
	return (bgr);
}

int	bgr_to_int(t_bgr bgr)
{
	return ((bgr.red << 16) | (bgr.green << 8) | (bgr.blue));
}

void	draw_pixel(t_image *img, const t_point *pixel)
{
	int	*location;

	if (img && (pixel->x >= START && pixel->x < WIN_WIDTH)
		&& (pixel->y >= START && pixel->y < WIN_HEIGHT))
	{
		location = (int *)(img->addr
				+ (pixel->y * img->row_len + pixel->x
					* (img->pixel_sizeof / SIZEOF_BYTE)));
		*location = bgr_to_int(pixel->color);
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

void	draw_line(t_image *img, t_point one, const t_point *second)
{
	int		distance[2];
	int		shifting;
	int		direction[2];

	distance[0] = abs(second->x - one.x);
	distance[1] = -abs(second->y - one.y);
	direction[0] = 1 - (2 * (one.x >= second->x));
	direction[1] = 1 - (2 * (one.y >= second->y));
	shifting = distance[0] + distance[1];
	while (one.x != second->x || one.y != second->y)
	{
		set_color(&(one.color), &(second->color), distance, shifting);
		draw_pixel(img, &one);
		if (shifting * 2 >= distance[1])
		{
			shifting += distance[1];
			one.x += direction[0];
		}
		if (shifting * 2 <= distance[0])
		{
			shifting += distance[0];
			one.y += direction[1];
		}
	}
}
