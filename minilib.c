/*
** EPITECH PROJECT, 2023
** B-MUL-100-LIL-1-1-myhunter-matisse.dufour
** File description:
** minilib.c
*/

void get_nbr_str(char *str, unsigned int score, int score_size)
{
    str[score_size] = '\0';
    for (int i = score_size - 1; i >= 0; i--) {
        str[i] = (score % 10) + '0';
        score /= 10;
    }
}

int my_intlen(unsigned int nb)
{
    int compt = 1;

    while (nb > 9) {
        compt++;
        nb /= 10;
    }
    return compt;
}

int my_strlen(char const *str)
{
    int counter = 0;

    while (*str != '\0'){
        ++counter;
        ++str;
    }
    return counter;
}

char *my_strcat(char *dest, char const *src)
{
    int start;
    int i;

    start = my_strlen(dest);
    for (i = 0; src[i] != '\0'; i++) {
        dest[i + start] = src[i];
    }
    dest[start + i] = '\0';
    return dest;
}
