/*
** EPITECH PROJECT, 2023
** B-MUL-100-LIL-1-1-myhunter-matisse.dufour
** File description:
** cursor.c
*/
#include "my_hunter.h"

void set_cursor(struct cursor_s *cursor, window_t *window)
{
    sfVector2i mouse_pos;
    sfVector2f new_pos = {0.0, 0.0};

    mouse_pos = (sfVector2i)sfMouse_getPositionRenderWindow(window->window);
    new_pos.x = (float)mouse_pos.x - (cursor->size.x * cursor->scale.x / 2.0);
    new_pos.y = (float)mouse_pos.y - (cursor->size.y * cursor->scale.y / 2.0);
    sfSprite_setPosition(cursor->sprite, new_pos);
    sfRenderWindow_setMouseCursorVisible(window->window, sfFalse);
}

int create_cursor(struct cursor_s *cursor, window_t *window)
{
    cursor->texture =
    sfTexture_createFromFile("ressources/sheets/crosshair.png", NULL);
    if (!cursor->texture)
        return 1;
    cursor->sprite = sfSprite_create();
    sfSprite_setTexture(cursor->sprite, cursor->texture, sfTrue);
    cursor->scale = (sfVector2f){1.0, 1.0};
    cursor->size = (sfVector2u)sfTexture_getSize(cursor->texture);
    sfSprite_setScale(cursor->sprite, cursor->scale);
    set_cursor(cursor, window);
    return 0;
}
