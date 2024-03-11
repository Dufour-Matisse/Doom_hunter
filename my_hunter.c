/*
** EPITECH PROJECT, 2023
** B-MUL-100-LIL-1-1-myhunter-matisse.dufour
** File description:
** my_hunter.c
*/

#include "my_hunter.h"
#include <SFML/Graphics.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Font.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Graphics/View.h>
#include <SFML/System.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Vector2.h>
#include <SFML/Window/Event.h>
#include <SFML/Window/VideoMode.h>
#include <SFML/Window/Window.h>
#include <unistd.h>
#include <stdlib.h>

static int init_ressources(window_t *window, weapon_t *weapon, mob_t *mob)
{
    if (create_window(window))
        return 1;
    if (set_high_score(window))
        return 1;
    if (create_cursor(&window->cursor, window))
        return 1;
    if (create_weapon(weapon, window))
        return 1;
    if (create_mob(mob, window))
        return 1;
    return 0;
}

static void game_event(window_t *window, mob_t *mob)
{
    if (((mob->position.x >= window->size.x && mob->speed > 0.0) ||
    (mob->position.x <= 0.0 && mob->speed < 0.0)) && mob->alive) {
        change_lives(window);
        mob->speed = (mob->scale.x < 0.0) ? -1.0 : 1.0;
        reset_mob(window, mob);
    }
    if (window->lives.lives <= 0) {
        menu(window, mob);
    }
}

static void animation(window_t *window, weapon_t *weapon, mob_t *mob)
{
    mob_animation(window, mob);
    sfRenderWindow_drawText(window->window, window->score.text, NULL);
    set_cursor(&window->cursor, window);
    sfRenderWindow_drawSprite(window->window, window->cursor.sprite, NULL);
    weapon_animation(window, weapon);
    sfText_setPosition(window->lives.text, (sfVector2f){0, window->size.y});
    sfRenderWindow_drawText(window->window, window->lives.text, NULL);
    sfRenderWindow_drawText(window->window, window->score.high_text, NULL);
}

static void destroy_loop(window_t *window, mob_t *mob)
{
    sfClock_destroy(mob->moving_clock);
    sfRenderWindow_destroy(window->window);
}

static void destroy(window_t *window, weapon_t *weapon, mob_t *mob)
{
    sfSprite_destroy(mob->sprite);
    sfTexture_destroy(mob->texture);
    sfSprite_destroy(weapon->sprite);
    sfTexture_destroy(weapon->texture);
    sfSprite_destroy(window->sprite);
    sfTexture_destroy(window->texture);
    sfSprite_destroy(window->cursor.sprite);
    sfTexture_destroy(window->cursor.texture);
    free(window->score.str);
    sfText_destroy(window->score.text);
    sfText_destroy(window->lives.text);
    free(window->lives.str);
    sfText_destroy(window->death.text);
    sfFont_destroy(window->score.font);
    sfText_destroy(window->score.high_text);
    free(window->score.high_str);
    sfFont_destroy(window->score.high_font);
    sfClock_destroy(weapon->animation_clock);
    sfClock_destroy(mob->animation_clock);
    destroy_loop(window, mob);
}

static int environment_check(char **env)
{
    for (int i = 0; env[i]; i++)
        if (!my_strncmp(env[i], "DISPLAY=", 8))
            return 0;
    return 1;
}

static int help(int argc, char **argv)
{
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == 'h') {
        write(1, "\tdoom_hunter (my_hunter)\n\nIn this duck hunt like game, "
        "you wield a big gun (because we love big guns) and you have to shoot "
        "the lost souls that going to appear on your screen with your big gun."
        " But be awarded, you have a pretty big reload time, so don't shoot "
        "anywhere.\n\nEach time you kill a lost soul the next one speed gonna "
        "increased by 2.5%%, more the lost soul go fast, more you get point. "
        "But if you let one pass you by, its speed is reset, and you lose 1 "
        "life, you start with 3 lives and at 0 lives you lost.\n\nYou can "
        "close the game by pressing escape.\n", 560);
            return 1;
        }
    }
    return 0;
}

static void game_loop(window_t *window, weapon_t *weapon, mob_t *mob)
{
    sfRenderWindow_clear(window->window, sfBlack);
    sfRenderWindow_drawSprite(window->window, window->sprite, NULL);
    game_event(window, mob);
    animation(window, weapon, mob);
    sfRenderWindow_display(window->window);
}

int main(int argc, char **argv, char **env)
{
    window_t window;
    weapon_t weapon;
    mob_t mob;
    sfEvent event;

    if (help(argc, argv))
        return 0;
    if (environment_check(env) || init_ressources(&window, &weapon, &mob))
        return 84;
    while (sfRenderWindow_isOpen(window.window)) {
        while (sfRenderWindow_pollEvent(window.window, &event))
            analyse_event(&window, event, &weapon, &mob);
        game_loop(&window, &weapon, &mob);
    }
    destroy(&window, &weapon, &mob);
    return 0;
}
