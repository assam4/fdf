/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:57:43 by saslanya          #+#    #+#             */
/*   Updated: 2025/03/04 22:13:53 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "matrix.h"
# include "mlx.h"

# define WIN_WIDTH 1200
# define WIN_HEIGHT 1000
# define SPACING 10
# define ANGLE_30 30
# define SIZEOF_BYTE 8
# define BLACK 0x0000
# define WHITE 0xffff

typedef struct s_window
{
	void	*mlx_connect;
	void	*window;
}	t_window;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		pixel_sizeof;
	int		row_len;
	int		endian;
}	t_image;

void	set_iso_matrix(t_matrix *object);
t_bgr	int_to_bgr(int color);
int		bgr_to_int(t_bgr bgr);
void	draw_pixel(t_image *img, const t_point *pixel);
void	draw_line(t_image *img, t_point one, const t_point *second);
#endif
