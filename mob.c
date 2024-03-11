/*
** EPITECH PROJECT, 2023
** B-MUL-100-LIL-1-1-myhunter-matisse.dufour
** File description:
** mob.c
*/

#include "my_hunter.h"
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Vector2.h>

static void set_mob_rect(mob_t *mob)
{
    mob->moving_frame[0] = (sfIntRect){236, 207, 302 - 236, 239 - 207};
    mob->moving_frame[1] = (sfIntRect){229, 284, 295 - 229, 316 - 284};
    mob->death_frame[0] = (sfIntRect){122, 448, 157 - 122, 500 - 448};
    mob->death_frame[1] = (sfIntRect){202, 448, 246 - 202, 495 - 448};
    mob->death_frame[2] = (sfIntRect){291, 448, 358 - 291, 507 - 448};
    mob->death_frame[3] = (sfIntRect){403, 448, 490 - 403, 519 - 448};
    mob->death_frame[4] = (sfIntRect){535, 448, 637 - 535, 537 - 448};
}

static int set_random_pos(mob_t *mob, window_t *window)
{
    int rand;

    rand = my_random(0, 1);
    if (rand == -1)
        return 1;
    if (rand) {
        mob->scale.x *= -1.0;
        mob->speed *= -1.0;
    }
    rand = my_random(50, (window->size.y * 0.8) - mob->moving_frame[0].height);
    mob->position = (sfVector2f){(float)(mob->scale.x < 0.0) ? window->size.x -
    (mob->moving_frame[0].width * mob->scale.x) : mob->moving_frame[0].width *
    -1.0 * mob->scale.x, (float)rand};
    return 0;
}

int create_mob(mob_t *mob, window_t *window)
{
    mob->texture = sfTexture_createFromFile("ressources/sheets/mob.png", NULL);
    if (!mob->texture)
        return 1;
    mob->sprite = sfSprite_create();
    sfSprite_setTexture(mob->sprite, mob->texture, sfTrue);
    set_mob_rect(mob);
    mob->scale = (sfVector2f){2.0, 2.0};
    mob->actual_frame = 0;
    mob->alive = 1;
    mob->animation_clock = sfClock_create();
    mob->moving_clock = sfClock_create();
    mob->speed = 1.0;
    set_random_pos(mob, window);
    sfSprite_setTextureRect(mob->sprite, mob->moving_frame[0]);
    sfSprite_setScale(mob->sprite, mob->scale);
    sfSprite_setPosition(mob->sprite, mob->position);
    return 0;
}

static void moving_animation(mob_t *mob, window_t *window)
{
    if (mob->scale.x > 0.0)
        mob->position.x = (TIME(mob->moving_clock) / 1500) * mob->speed -
        mob->moving_frame[mob->actual_frame].width * mob->scale.x;
    else
        mob->position.x = window->size.x +
        (mob->moving_frame[mob->actual_frame].width * ABS(mob->scale.x)) +
        ((TIME(mob->moving_clock) / 1500) * mob->speed);
    if (TIME(mob->animation_clock) > 150000) {
        sfClock_restart(mob->animation_clock);
        sfSprite_setTextureRect(mob->sprite,
        mob->moving_frame[mob->actual_frame]);
        mob->actual_frame++;
    }
    if (mob->actual_frame >= 2)
        mob->actual_frame = 0;
}

static void death_animation(mob_t *mob, window_t *window)
{
    float caca;

    if (TIME(mob->animation_clock) < 125000)
        return;
    if (mob->actual_frame >= 5) {
        reset_mob(window, mob);
        return;
    }
    sfClock_restart(mob->animation_clock);
    caca = mob->death_frame[mob->actual_frame].width;
    mob->position = (sfVector2f){(float)mob->middle.x +
    (mob->scale.x < 0.0 ? -caca : caca), mob->middle.y -
    (mob->death_frame[mob->actual_frame].height)};
    sfSprite_setTextureRect(mob->sprite, mob->death_frame[mob->actual_frame]);
    mob->actual_frame++;
}

void mob_animation(window_t *window, mob_t *mob)
{
    if (mob->alive)
        moving_animation(mob, window);
    else
        death_animation(mob, window);
    sfSprite_setPosition(mob->sprite, mob->position);
    sfRenderWindow_drawSprite(window->window, mob->sprite, NULL);
}

void reset_mob(window_t *window, mob_t *mob)
{
    mob->actual_frame = 0;
    mob->alive = 1;
    set_random_pos(mob, window);
    sfClock_restart(mob->animation_clock);
    sfClock_restart(mob->moving_clock);
    sfSprite_setTextureRect(mob->sprite, mob->moving_frame[0]);
    sfSprite_setScale(mob->sprite, mob->scale);
    sfSprite_setPosition(mob->sprite, mob->position);
}
