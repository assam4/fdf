#include "fdf.h"
/*
int main(void)
{
	int color = 0;
	t_matrix *object = ft_calloc(1, sizeof(t_matrix));
	if (object)
	{
		int fd = open("test.txt", O_RDONLY);
		if (fd < 2)
			return (VALIDATION_ERROR);
		int status = file_format_checking(fd, &(object->columns), &(object->rows));
		close(fd);
		if (status == SUCCESS)
		{
			printf("FILE IS VALID!\n");
			printf("%i || %i \n", object->rows, object->columns);
			fd = open("test.txt", O_RDONLY);
			if (fd < 2)
				return (VALIDATION_ERROR);
			status = initialize_matrix(fd, object);
			close(fd);
			set_iso_matrix(object);
			for (int y = 0; y < object->rows; ++y)
			{
				for(int x = 0; x < object->columns; ++x)
				{
					color_transform(&(object->pixels[y][x].color), &color, TO_INT);
					printf("[%i %i %i color(int): %i] ", 
						object->pixels[y][x].y,
						object->pixels[y][x].x,
						object->pixels[y][x].z,
						color);
				}
			printf("\n");
			}
		}
	deallocate_matrix(&object);
	}
	return (0);
}


#include "graphics.h"

int main(void)
{
    t_window window;
    t_image img;
    t_matrix *matrix = ft_calloc(1, sizeof(t_matrix));  // Пример вашей матрицы

    int	fd = open("test.txt",O_RDONLY);
    initialize_matrix(fd, matrix);
    set_iso_matrix(matrix);
 
    window.mlx_connect = mlx_init();
    window.window = mlx_new_window(window.mlx_connect, WIN_WIDTH, WIN_HEIGHT, "FdF");
    img.img = mlx_new_image(window.mlx_connect, WIN_WIDTH, WIN_HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.pixel_sizeof, &img.row_len, &img.endian);
    draw_matrix(&img, matrix);
    mlx_put_image_to_window(window.mlx_connect, window.window, img.img, 0, 0);

    // Основной цикл обработки событий
    mlx_loop(window.mlx_connect);

    return 0;
}
*/
#include "graphics.h"
#include <fcntl.h>   // Для open
#include <unistd.h>  // Для close
int close_window(int keycode, t_window *win)
{
    if (keycode == 65307) // ESC
    {
        mlx_destroy_window(win->mlx_connect, win->window);
        exit(0);
    }
    return (0);
}

int main(void)
{
    t_window window;
    t_image img;
    t_matrix *matrix = ft_calloc(1, sizeof(t_matrix));

    // Открываем и инициализируем матрицу
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Failed to open file");
        return (1);
    }
    file_format_checking(fd, &(matrix->columns), &(matrix->rows));
    close(fd);
    fd = open("test.txt", O_RDONLY);
    initialize_matrix(fd, matrix);
    printf("Matrix rows: %d, columns: %d\n", matrix->rows, matrix->columns);
    set_iso_matrix(matrix);
    close(fd);

    // Инициализация MLX
    window.mlx_connect = mlx_init();
    window.window = mlx_new_window(window.mlx_connect, WIN_WIDTH, WIN_HEIGHT, "FdF");

    // Создание изображения
    img.img = mlx_new_image(window.mlx_connect, WIN_WIDTH, WIN_HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.pixel_sizeof, &img.row_len, &img.endian);

    // Рисуем матрицу на изображении
    draw_matrix(&img, matrix);
	printf("DONE\n");
    // Отображаем изображение в окне
    mlx_put_image_to_window(window.mlx_connect, window.window, img.img, 0, 0);

    // Обработчик закрытия окна (например, при нажатии на ESC)
    mlx_key_hook(window.window, close_window, &window);

    // Основной цикл обработки событий
    mlx_loop(window.mlx_connect);

    return (0);
}
