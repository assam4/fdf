NAME = fdf

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
#FRAMEWORKS = -framework OpenGl -framework AppKit #MacOS
FRAMEWORKS = -lXext -lX11 -lm -lz #LINUX

LIBFT = ./library/libft/
GNL = ./library/get_next_line/
MLX = ./library/minilibx/
VALIDATION = ./file_validation/
MATRIX = ./matrix/
GRAPHICS = ./graphics/
FDF = ./fdf_viewer/
INCLUDES = -I$(LIBFT) -I$(GNL) -I$(MLX) -I$(VALIDATION) -I$(MATRIX) -I$(GRAPHICS) -I$(FDF)

SRCS = $(GNL)get_next_line.c $(GNL)get_next_line_utils.c $(VALIDATION)validation_utils.c \
       $(MATRIX)matrix.c $(GRAPHICS)draw.c $(GRAPHICS)draw_utils.c $(GRAPHICS)view.c \
        $(FDF)/fdf.c  $(FDF)/fdf_utils.c main.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT)libft.a $(MLX)libmlx.a $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -L$(MLX) -lmlx -L$(LIBFT) -lft $(FRAMEWORKS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT)libft.a:
	$(MAKE) -C $(LIBFT)

$(MLX)libmlx.a:
	$(MAKE) -C $(MLX)

clean:
	$(MAKE) -C $(LIBFT) clean
	$(MAKE) -C $(MLX) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
