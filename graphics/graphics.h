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

//window utils
# define TITLE "FDF project by saslanya"
# define WIN_WIDTH 1200
# define WIN_HEIGHT 1000
# define SPACING 10
# define SIZEOF_BYTE 8

// isometric projection
# define ANGLE_30 0.523599

// perspective proejction
# define FOCAL_LENGTH 500.0
# define CAMERA_DISTANCE 100.0
# define MIN_DIVISOR 0.01

// colors in hex (bgr)
# define BLACK 0x000000
# define BLUE 0x0000FF
# define WHITE 0xFFFFFF
# define BORDO 0x800000
# define YELLOW 0xFFFF00
# define GREEN 0x00FF00
# define PURPLE 0x800080

typedef struct s_data
{
	void			*mlx_connect;
	void			*window;
	void			*img;
	char			*addr;
	int				pixel_sizeof;
	int				row_len;
	int				endian;
	t_matrix		*matrix;
	void			(*projection)(t_matrix *matrix);
}	t_data;

// draw_utils functions
void	color_transform(t_bgr *bgr, int *color, int swap_source);
void	set_colors(t_matrix *matrix);
void	calc_color(t_bgr *current, const t_bgr *diff);

// draw functions
void	draw_matrix(t_data *img, void (*transform)(t_matrix *m));

// projections
void	to_isometric(t_matrix *matrix);
void	to_perspective(t_matrix *matrix);

#endif
