/*
** EPITECH PROJECT, 2023
** B-MUL-100-LIL-1-1-myhunter-matisse.dufour
** File description:
** my_hunter.h
*/

#ifndef MY_HUNTER
    #define MY_HUNTER
    #include <SFML/Graphics.h>
    #include <SFML/Graphics/Rect.h>
    #include <SFML/Graphics/Types.h>
    #include <SFML/System/Clock.h>
    #include <SFML/System/Types.h>
    #include <SFML/System/Vector2.h>
    #define TIME(clock) sfClock_getElapsedTime(clock).microseconds
    #define ABS(nb) ((nb) < 0.0 ? -(nb) : (nb))

typedef struct weapon_s {
    sfTexture *texture;
    sfSprite *sprite;
    sfVector2f scale;
    sfIntRect default_frame;
    sfIntRect reload_frame[7];
    sfIntRect shoot_frame[2];
    int shooting_frame;
    sfClock *animation_clock;
} weapon_t;

struct cursor_s {
    sfTexture *texture;
    sfSprite *sprite;
    sfVector2f scale;
    sfVector2u size;
};

struct score {
    sfFont *font;
    sfText *text;
    char *str;
    unsigned int score;
    sfFloatRect text_rect;
    sfFont *high_font;
    sfText *high_text;
    unsigned int high_score;
    char *high_str;
    sfFloatRect high_rect;
};

struct lives {
    sfFont *font;
    sfText *text;
    char *str;
    unsigned int lives;
};

struct death_message {
    sfText *text;
    sfFloatRect text_rect;
    sfText *subtext;
    sfFloatRect subtext_rec;
};

typedef struct window_s {
    sfRenderWindow *window;
    sfTexture *texture;
    sfSprite *sprite;
    sfVector2f scale;
    sfVector2u size;
    struct cursor_s cursor;
    struct score score;
    struct lives lives;
    struct death_message death;
} window_t;

typedef struct mob_s {
    sfTexture *texture;
    sfSprite *sprite;
    sfIntRect moving_frame[2];
    sfIntRect death_frame[5];
    int actual_frame;
    int alive;
    sfVector2f scale;
    sfVector2f position;
    sfVector2u middle;
    float speed;
    sfClock *animation_clock;
    sfClock *moving_clock;
} mob_t;

int my_random(int min, int max);
int my_strncmp(char const *s1, char const *s2, int n);
void get_nbr_str(char *str, unsigned int score, int score_size);
int my_intlen(unsigned int nb);
int my_strlen(char const *str);
char *my_strcat(char *dest, char const *src);
int create_window(window_t *window);
int create_weapon(weapon_t *weapon, window_t *window);
void weapon_position(window_t *window, weapon_t *weapon);
void weapon_animation(window_t *window, weapon_t *weapon);
int create_mob(mob_t *mob, window_t *window);
void mob_animation(window_t *window, mob_t *mob);
void reset_mob(window_t *window, mob_t *mob);
int create_cursor(struct cursor_s *cursor, window_t *window);
void set_cursor(struct cursor_s *cursor, window_t *window);
void analyse_event(window_t *window, sfEvent event, weapon_t *weapon,
    mob_t *mob);
void resized_window(window_t *window, sfEvent event);
int set_score(struct score *score);
int set_high_score(window_t *window);
void edit_score(struct score *score, int mob_point);
void change_lives(window_t *window);
void menu(window_t *window, mob_t *mob);
int set_death(window_t *window);
void check_new_record(window_t *window);
#endif
