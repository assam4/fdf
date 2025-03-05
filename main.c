#include "fdf.h"

int main(void)
{
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
			printf("%i || %i \n", object->columns, object->rows);
			fd = open("test.txt", O_RDONLY);
			if (fd < 2)
				return (VALIDATION_ERROR);
			status = initialize_matrix(fd, object);
			close(fd);
			set_iso_matrix(object);
			for (int x = 0; x < object->rows; ++x)
			{
				for(int y = 0; y < object->columns; ++y)
					printf("[%i %i %i] ", 
						object->pixels[x][y].x,
						object->pixels[x][y].y,
						object->pixels[x][y].z);
			printf("\n");
			}
		}
	deallocate_matrix(&object);
	}
	return (0);
}

