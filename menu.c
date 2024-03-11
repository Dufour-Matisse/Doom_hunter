/*
** EPITECH PROJECT, 2023
** B-MUL-100-LIL-1-1-myhunter-matisse.dufour
** File description:
** menu.c
*/

#include "my_hunter.h"
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window/Event.h>
#include <SFML/Window/Keyboard.h>

int set_death(window_t *window)
{
    window->death.text = sfText_create();
    sfText_setFont(window->death.text, window->score.font);
    sfText_setString(window->death.text, "Game over");
    sfText_setCharacterSize(window->death.text, 100);
    window->death.text_rect = sfText_getGlobalBounds(window->death.text);
    window->death.subtext = sfText_create();
    sfText_setFont(window->death.subtext, window->score.font);
    sfText_setString(window->death.subtext, "Press 'r' to restart\n"
    " Press 'esc' to quit");
    sfText_setCharacterSize(window->death.subtext, 50);
    window->death.subtext_rec = sfText_getGlobalBounds(window->death.text);
    return 0;
}

static void set_death_text_pos(window_t *window)
{
    sfText_setPosition(window->death.text, (sfVector2f){(window->size.x -
    window->death.text_rect.width) / 2, window->size.y * 0.1});
    window->score.text_rect = sfText_getGlobalBounds(window->score.text);
    sfText_setPosition(window->score.text, (sfVector2f){(window->size.x -
    window->score.text_rect.width) / 2, window->size.y * 0.15 +
    window->death.text_rect.height});
    sfText_setPosition(window->score.high_text, (sfVector2f){(window->size.x +
    window->score.high_rect.width) / 2, window->size.y * 0.2 +
    window->death.text_rect.height + window->score.text_rect.height});
    sfText_setPosition(window->death.subtext, (sfVector2f){(window->size.x -
    window->death.subtext_rec.width) / 2, window->size.y *
    0.25 + window->death.text_rect.height + window->score.text_rect.height +
    window->score.high_rect.height});
}

void menu_event(window_t *window, sfEvent event, int *menu_opened)
{
    if (event.type == sfEvtClosed || (event.type == sfEvtKeyPressed &&
    event.key.code == sfKeyEscape))
        sfRenderWindow_close(window->window);
    if (event.type == sfEvtKeyPressed && event.key.code == sfKeyR) {
        *menu_opened = 0;
    }
    if (event.type == sfEvtResized)
        resized_window(window, event);
}

void restart_game(window_t *window, mob_t *mob)
{
    window->size = sfRenderWindow_getSize(window->window);
    window->score.score = 0;
    edit_score(&window->score, 0);
    sfText_setPosition(window->score.text, (sfVector2f){0.0, 0.0});
    sfText_setPosition(window->score.high_text, (sfVector2f){window->size.x,
    0.0});
    window->lives.lives = 3;
    window->lives.str[7] = '3';
    sfText_setString(window->lives.text, window->lives.str);
    reset_mob(window, mob);
}

void menu(window_t *window, mob_t *mob)
{
    sfEvent event;
    int menu_opened = 1;

    set_death_text_pos(window);
    while (sfRenderWindow_isOpen(window->window) && menu_opened) {
        while (sfRenderWindow_pollEvent(window->window, &event))
            menu_event(window, event, &menu_opened);
        sfRenderWindow_clear(window->window, sfBlack);
        sfRenderWindow_drawText(window->window, window->death.subtext, NULL);
        sfRenderWindow_drawText(window->window, window->score.text, NULL);
        sfRenderWindow_drawText(window->window, window->score.high_text, NULL);
        sfRenderWindow_drawText(window->window, window->death.text, NULL);
        sfRenderWindow_display(window->window);
    }
    check_new_record(window);
    sfText_setOrigin(window->score.high_text,
    (sfVector2f){window->score.high_rect.width, 0.0});
    if (!menu_opened) {
        restart_game(window, mob);
    }
}
