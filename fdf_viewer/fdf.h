#ifndef FDF_H
# define FDF_H

# include "graphics.h"

# define UNCHANGE 0
# define STEPS 5
# define ROTATE_STEP 0.174533
# define ANGLE_360 360

# define ESC 65307
# define UP 65362
# define DOWN 65364
# define RIGHT 65363
# define LEFT 65361
# define ZOOM_IN 65451
# define ZOOM_OUT 65453

# define CHANGE_COLORS 'c'
# define ISOMETRIC 'i'
# define PERSPECTIVE 'p'

# define FOPEN_ERR -1
# define CLOSE_WINDOW 17
# define KEY_PRESS 1L
# define FORMAT_START '.'
# define FILE_FORMAT ".fdf"

t_matrix	*get_matrix(const char *fname);
void		run_fdf(t_data *data);
void		reset_img(t_data *data);
void		shift_or_zoom(int key, t_matrix *matrix);
void		rotate(int key, t_matrix *matrix);
int			update_window(t_data *data);

#endif
