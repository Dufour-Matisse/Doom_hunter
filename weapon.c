/*
** EPITECH PROJECT, 2023
** B-MUL-100-LIL-1-1-myhunter-matisse.dufour
** File description:
** weapon.c
*/

#include "my_hunter.h"
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Vector2.h>

static void set_weapon_rect(weapon_t *weapon)
{
    weapon->reload_frame[0] = (sfIntRect){607, 207, 689 - 607, 309 - 207};
    weapon->reload_frame[1] = (sfIntRect){693, 180, 813 - 693, 309 - 180};
    weapon->reload_frame[2] = (sfIntRect){817, 230, 897 - 817, 309 - 230};
    weapon->reload_frame[3] = (sfIntRect){901, 247, 1101 - 901, 309 - 247};
    weapon->reload_frame[4] = (sfIntRect){1105, 259, 1192 - 1105, 309 - 259};
    weapon->reload_frame[5] = (sfIntRect){1196, 230, 1276 - 1196, 309 - 230};
    weapon->reload_frame[6] = (sfIntRect){1280, 225, 1356 - 1280, 309 - 225};
    weapon->shoot_frame[0] = (sfIntRect){566, 167, 621 - 566, 203 - 167};
    weapon->shoot_frame[1] = (sfIntRect){625, 158, 689 - 625, 203 - 158};
}

static void weapon_scale(weapon_t *weapon, window_t *window)
{
    if (ABS(1920 - window->size.x) <= (ABS(1080 - window->size.y))) {
    weapon->scale.x = (4.0 / (float)1920) * (float)window->size.x;
    weapon->scale.y = (4.0 / (float)1920) * (float)window->size.x;
    } else {
    weapon->scale.x = (4.0 / (float)1080) * (float)window->size.y;
    weapon->scale.y = (4.0 / (float)1080) * (float)window->size.y;
    }
    sfSprite_setScale(weapon->sprite, weapon->scale);
}

int create_weapon(weapon_t *weapon, window_t *window)
{
    weapon->texture = sfTexture_createFromFile("ressources/sheets/weapon.png",
    NULL);
    if (!weapon->texture)
        return 1;
    weapon->sprite = sfSprite_create();
    sfSprite_setTexture(weapon->sprite, weapon->texture, sfTrue);
    weapon->default_frame = (sfIntRect){545, 256, 603 - 545, 310 - 256};
    set_weapon_rect(weapon);
    weapon->animation_clock = sfClock_create();
    weapon->shooting_frame = -1;
    weapon->scale = (sfVector2f){4.0, 4.0};
    sfSprite_setTextureRect(weapon->sprite, weapon->default_frame);
    weapon_position(window, weapon);
    sfSprite_setScale(weapon->sprite, weapon->scale);
    return 0;
}

void weapon_position(window_t *window, weapon_t *weapon)
{
    sfVector2f sprite_pos;
    sfFloatRect sprite_size;

    weapon_scale(weapon, window);
    sprite_size = sfSprite_getGlobalBounds(weapon->sprite);
    sprite_pos.x = (window->size.x - sprite_size.width) / 2.0;
    sprite_pos.y = (window->size.y - sprite_size.height);
    sfSprite_setPosition(weapon->sprite, sprite_pos);
}

void weapon_animation(window_t *window, weapon_t *weapon)
{
    if ((weapon->shooting_frame == 7 || weapon->shooting_frame == -1) &&
    TIME(weapon->animation_clock) > 200000){
        weapon->shooting_frame = -1;
        sfSprite_setTextureRect(weapon->sprite, weapon->default_frame);
        weapon_position(window, weapon);
    } else if (TIME(weapon->animation_clock) > 200000) {
        sfSprite_setTextureRect(weapon->sprite,
        weapon->reload_frame[weapon->shooting_frame]);
        weapon->shooting_frame++;
        sfClock_restart(weapon->animation_clock);
        weapon_position(window, weapon);
    }
    sfRenderWindow_drawSprite(window->window, weapon->sprite, NULL);
}
