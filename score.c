/*
** EPITECH PROJECT, 2023
** B-MUL-100-LIL-1-1-myhunter-matisse.dufour
** File description:
** score.c
*/
#include "my_hunter.h"
#include <SFML/Graphics/Font.h>
#include <SFML/Graphics/Text.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void check_new_record(window_t *window)
{
    int fd;
    int num_size;

    if (window->score.score <= window->score.high_score)
        return;
    fd = open("high_score", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0)
        return;
    num_size = my_strlen(window->score.str + 7);
    write(fd, window->score.str + 7, num_size);
    close(fd);
    free(window->score.high_str);
    window->score.high_str = malloc(13 + num_size);
    window->score.high_str[0] = '\0';
    my_strcat(window->score.high_str, "High score: ");
    my_strcat(window->score.high_str, window->score.str + 7);
    window->score.high_score = window->score.score;
    sfText_setString(window->score.high_text, window->score.high_str);
    window->score.high_rect = sfText_getGlobalBounds(window->score.high_text);
}

static int get_high_score(window_t *window)
{
    int fd;
    char buff[10];
    int readed;

    window->score.high_score = 0;
    fd = open("high_score", O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd < 0)
        return 1;
    do {
        readed = read(fd, buff, 10);
        for (int i = 0; i < readed && buff[i] <= '9' && buff[i] >= '0'; i++) {
            window->score.high_score *= 10;
            window->score.high_score += buff[i] - '0';
        }
    } while (readed > 0);
    close(fd);
    return 0;
}

static void get_score_str(window_t *window)
{
    int len_nb;
    char *str;

    len_nb = my_intlen(window->score.high_score);
    window->score.high_str = malloc(13 + len_nb);
    window->score.high_str[0] = '\0';
    my_strcat(window->score.high_str, "High score: ");
    str = malloc(len_nb + 1);
    get_nbr_str(str, window->score.high_score, len_nb);
    my_strcat(window->score.high_str, str);
    free(str);
}

int set_high_score(window_t *window)
{
    if (get_high_score(window))
        return 1;
    get_score_str(window);
    window->score.high_font =
    sfFont_createFromFile("ressources/font/doom_font2.ttf");
    if (!window->score.high_font)
        return 1;
    window->score.high_text = sfText_create();
    sfText_setFont(window->score.high_text, window->score.high_font);
    sfText_setCharacterSize(window->score.high_text, 75);
    sfText_setString(window->score.high_text, window->score.high_str);
    window->score.high_rect = sfText_getGlobalBounds(window->score.high_text);
    sfText_setOrigin(window->score.high_text,
    (sfVector2f){window->score.high_rect.width, 0.0});
    sfText_setPosition(window->score.high_text, (sfVector2f){window->size.x,
    0.0});
    return 0;
}

void edit_score(struct score *score, int mob_point)
{
    char *str;
    int score_size;

    free(score->str);
    score->score += mob_point;
    score_size = my_intlen(score->score);
    score->str = malloc(8 + score_size);
    score->str[0] = '\0';
    my_strcat(score->str, "Score: ");
    str = malloc(score_size + 1);
    get_nbr_str(str, score->score, score_size);
    my_strcat(score->str, str);
    free(str);
    sfText_setString(score->text, score->str);
}

int set_score(struct score *score)
{
    char *str;
    int score_size;

    score->font = sfFont_createFromFile("ressources/font/doom_font.ttf");
    if (!score->font)
        return 1;
    score->text = sfText_create();
    score->score = 0;
    score_size = my_intlen(score->score);
    score->str = malloc(8 + score_size);
    score->str[0] = '\0';
    my_strcat(score->str, "Score: ");
    str = malloc(score_size + 1);
    get_nbr_str(str, score->score, score_size);
    my_strcat(score->str, str);
    free(str);
    sfText_setFont(score->text, score->font);
    sfText_setCharacterSize(score->text, 75);
    sfText_setString(score->text, score->str);
    return 0;
}
