/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:57:43 by saslanya          #+#    #+#             */
/*   Updated: 2025/05/10 17:25:25 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "matrix.h"
# include "mlx.h"

# define TITLE "FDF project by saslanya"
# define WIN_WIDTH 1200
# define WIN_HEIGHT 1000
# define SPACING 10

// isometric projection
# define ANGLE_30 0.523599

// perspective proejction
# define FOCAL_LENGTH 500.0
# define CAMERA_DISTANCE 100.0
# define MIN_DIVISOR 0.01

// colors in hex (bgr)
# define BLACK 0x000000
# define COLOR1 0xFFFF00	
# define COLOR2 0xFFFFFF
# define COLOR3 0x000080

# define ROTATE_X 'x'
# define ROTATE_Y 'y'
# define ROTATE_Z 'z'

typedef struct s_data
{
	void			*mlx_connect;
	void			*window;
	void			*img;
	char			*addr;
	int				pixel_sizeof;
	int				row_len;
	int				endian;
	int				is_changed;
	t_matrix		*matrix;
	void			(*projection)(t_matrix *matrix);
}	t_data;

void	change_color(t_point *pixel);
void	set_def_colors(t_point *pixel);
void	set_colors(t_matrix *matrix, void (*setter)(t_point *));
void	calc_color(t_bgr *current, const t_bgr *diff);

// draw functions
void	draw_matrix(t_data *img, void (*transform)(t_matrix *m));

// projections
void	to_isometric(t_matrix *matrix);
void	to_perspective(t_matrix *matrix);

#endif
