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

# define TITLE "FDF project by saslanya"
# define WIN_WIDTH 1200
# define WIN_HEIGHT 1000
# define SPACING 10
# define ANGLE_30 0.523599
# define ANGLE_360 360
# define SIZEOF_BYTE 8

# define BLACK 0x000000
# define BLUE 0x0000FF
# define WHITE 0xFFFFFF
# define BORDO 0x800000
# define YELLOW 0xFFFF00
# define GREEN 0x00FF00
# define PURPLE 0x800080

# define STEPS 5
# define ROTATE_STEP (10 * (M_PI / 180))
# define UNCHANGE 0
# define ESC 65307
# define UP 65362
# define DOWN 65364
# define RIGHT 65363
# define LEFT 65361
# define ZOOM_IN 65451
# define ZOOM_OUT 65453

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
}	t_data;

void	draw_line(t_data *img, t_point current, const t_point *end);
void	color_transform(t_bgr *bgr, int *color, int swap_source);
void	set_colors(t_matrix *matrix);
void	draw_matrix(t_data *img, void (*transform)(t_matrix *m));
void	to_isometric(t_matrix *matrix);

#endif
