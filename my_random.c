/*
** EPITECH PROJECT, 2023
** return random number
** File description:
** func with time return random num
*/
#include <fcntl.h>
#include <unistd.h>

int my_random(int min, int max)
{
    int a;
    int fd;

    max += 1;
    fd = open("/dev/urandom", O_RDONLY);
    if (fd == -1) {
        write(2, "An error occured while trying to open '/dev/urandom'\n", 53);
        return -1;
    }
    read(fd, &a, sizeof(int));
    a = a < 0 ? a * -1 : a;
    a = a % (max - min) + min;
    close(fd);
    return a;
}
