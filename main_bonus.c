
#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
    int fd1, fd2;
    char *line1 = NULL;
    char *line2 = NULL;

    fd1 = open("empty.txt", O_RDONLY);
    fd2 = open("hola.txt", O_RDONLY);

    if (fd1 == -1 || fd2 == -1)
    {
        perror("Error al abrir los archivos");
        if (fd1 != -1)
            close(fd1);
        if (fd2 != -1)
            close(fd2);
        return (1);
    }

    printf("Leyendo de manera simultánea de empty.txt y hola.txt:\n");

    while (1)
    {
        int read1 = 0, read2 = 0;

        if ((line1 = get_next_line(fd1)) != NULL)
        {
            printf("empty.txt: %s\n", line1);
            free(line1);
            read1 = 1;
        }
        if ((line2 = get_next_line(fd2)) != NULL)
        {
            printf("hola.txt: %s\n", line2);
            free(line2);
            read2 = 1;
        }
        if (!read1 && !read2)
            break;
    }

    close(fd1);
    close(fd2);

    return (0);
}
