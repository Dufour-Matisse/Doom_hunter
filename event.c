/*
** EPITECH PROJECT, 2023
** B-MUL-100-LIL-1-1-myhunter-matisse.dufour
** File description:
** event.c
*/

#include "my_hunter.h"

static void manage_mouse_click(weapon_t *weapon, sfMouseButtonEvent click,
    mob_t *mob, struct score *score)
{
    sfIntRect hitbox = {0, 0, 0, 0};

    if (weapon->shooting_frame != -1)
        return;
    weapon->shooting_frame = 0;
    hitbox.width = mob->moving_frame[mob->actual_frame].width *
    (ABS(mob->scale.x));
    hitbox.height = mob->moving_frame[mob->actual_frame].height *
    (ABS(mob->scale.y));
    hitbox.top = mob->position.y;
    hitbox.left = mob->position.x - ((mob->scale.x < 0.0) ? hitbox.width : 0);
    if (click.x >= hitbox.left && ((click.x - hitbox.width) < hitbox.left) &&
    (click.y >= hitbox.top) && ((click.y - hitbox.height) < hitbox.top)) {
        mob->alive = 0;
        mob->middle = (sfVector2u){hitbox.left + (hitbox.width / 2), hitbox.top
        + (hitbox.height / 2)};
        mob->actual_frame = 1;
        edit_score(score, 100 * ABS(mob->speed));
        mob->speed *= 1.025;
    }
}

void analyse_event(window_t *window, sfEvent event,
    weapon_t *weapon, mob_t *mob)
{
    if (event.type == sfEvtClosed || (event.type == sfEvtKeyPressed &&
    event.key.code == sfKeyEscape))
        sfRenderWindow_close(window->window);
    if (event.type == sfEvtMouseButtonPressed)
        manage_mouse_click(weapon, event.mouseButton, mob, &window->score);
    if (event.type == sfEvtResized)
        resized_window(window, event);
}
