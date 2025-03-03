
#include "get_next_line_bonus.h"

int main(void)
{
    int fd1, fd2;
    char *line;

    fd1 = open("empty.txt", O_RDONLY);
    fd2 = open("hola.txt", O_RDONLY);

    if (fd1 == -1 || fd2 == -1)
    {
        perror("Error al abrir los archivos");
        return (1);
    }

    printf("Leyendo de file1.txt:\n");
    while ((line = get_next_line(fd1)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    printf("\nLeyendo de file2.txt:\n");
    while ((line = get_next_line(fd2)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd1);
    close(fd2);

    return (0);
}
