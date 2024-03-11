/*
** EPITECH PROJECT, 2023
** B-MUL-100-LIL-1-1-myhunter-matisse.dufour
** File description:
** window.c
*/

#include "my_hunter.h"
#include <SFML/Graphics.h>
#include <SFML/Graphics/Font.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/Text.h>
#include <stdlib.h>

void change_lives(window_t *window)
{
    window->lives.lives -= 1;
    window->lives.str[7] = window->lives.lives + '0';
    sfText_setString(window->lives.text, window->lives.str);
}

void init_lives(window_t *window)
{
    sfFloatRect text_rect;

    window->lives.font = window->score.font;
    window->lives.text = sfText_create();
    window->lives.lives = 3;
    window->lives.str = malloc(9);
    window->lives.str[0] = '\0';
    my_strcat(window->lives.str, "Lives: 3");
    sfText_setFont(window->lives.text, window->lives.font);
    sfText_setString(window->lives.text, window->lives.str);
    sfText_setCharacterSize(window->lives.text, 75);
    text_rect = sfText_getGlobalBounds(window->lives.text);
    sfText_setOrigin(window->lives.text, (sfVector2f){text_rect.left,
    text_rect.height});
    sfText_setPosition(window->lives.text, (sfVector2f){0, window->size.y});
}

void resized_window(window_t *window, sfEvent event)
{
    sfFloatRect visible_area;

    visible_area = (sfFloatRect){0, 0, (float)event.size.width,
    (float)event.size.height};
    sfRenderWindow_setView(window->window,
    sfView_createFromRect(visible_area));
    window->size = sfRenderWindow_getSize(window->window);
}

int create_window(window_t *window)
{
    sfVideoMode mode = {1920, 1080, 32};

    window->window = sfRenderWindow_create(mode, "doom_hunter",
    sfResize | sfClose, NULL);
    if (!window->window)
        return 1;
    window->texture =
    sfTexture_createFromFile("ressources/nico_background.png", NULL);
    if (!window->texture)
        return 1;
    window->sprite = sfSprite_create();
    sfSprite_setTexture(window->sprite, window->texture, sfTrue);
    window->scale = (sfVector2f){1.0, 1.0};
    sfSprite_setScale(window->sprite, window->scale);
    window->size = sfRenderWindow_getSize(window->window);
    sfRenderWindow_setFramerateLimit(window->window, 60);
    if (set_score(&window->score) || set_death(window))
        return 1;
    init_lives(window);
    return 0;
}
