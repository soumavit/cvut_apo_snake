/**
 * game_utils.h
 * 
 * file containg function that are used to run the snake game
 * also a fruit struct is defined here which is needed to run the game aswell
 * 
 * snake is defined in snake_t.h file as its own structure with its own functions
 * 
 * created by Vit Soumar and Marek Jirku for computer architectures course semestral project
*/


#ifndef __GAME_UTILS_H__
#define __GAME_UTILS_H__


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "types/snake_t.h"
#include "utils/theme_utils.h"

/**
 * holds x, y coordinates of the fruit
*/
typedef struct fruit_t{
    int x;
    int y;
} fruit_t;

/**
 * creates a fruit struct and returns a pointer to it
*/
fruit_t* fruit_init();

/**
 * randomly sets fruit pos in the game field with width w and height w
 * also depending on the game tile size and snake position
*/
void move_fruit_random(fruit_t* fruit, snake_t* snake, int w, int h);

/**
 * randomly sets fruit pos in the game field with width w and height w
 * also depending on the game tile size and the position of both snakes
*/
void move_fruit_random_2(fruit_t* fruit, snake_t* snake1, snake_t* snake2, int w, int h);

/**
 * redraws the game field with updated snake position, updated fruit position (if the fruit has moved)
 * everything is draw with its colors to the display buffer
*/
void update_game_display(unsigned int** buffer, snake_t* s, fruit_t* f, unsigned int backgound_c, int w, int h);

/**
 * redraws the game field with updated snakes position, updated fruit position (if the fruit has moved)
 * everything is draw with its colors to the display buffer
*/
void update_game_display_2(unsigned int** buffer, snake_t* s1, snake_t* s2, fruit_t* f, unsigned int backgound_c, int w, int h);

/**
 * checks it the snake s has collided with a wall
 * (game field size is defined by the width w and height h)
 * returns true if snake collided, false otherwise
*/
bool collision(snake_t* s, int w, int h);

/**
 * checks it the snake s1 has collided with a wall
 * checks if the snake s2 has collided with a wall
 * (game field size is defined by the width w and height h)
 * checks if snakes collided with each other
 * returns true if at least one of the snakes collided, false otherwise
*/
bool collision_2(snake_t* this, snake_t* other, int w, int h);

/**
 * draws snake to the display buffer
*/
void draw_snake(unsigned int** buffer, snake_t* s, unsigned int color, unsigned int border_color);

/**
 * draw one snake tile to the display buffer
*/
void draw_snake_tile(unsigned int** buffer, int x, int y, unsigned int snake_c, unsigned int border_c);

/**
 * update displayed text in the score counter button
*/
void update_score(unsigned int **buffer, button_t* score_counter, int score);

/**
 * sets game speed depending on the SNAKE_SPEED define in global_values.h
*/
int set_game_speed();

#endif /*__GAME_UTILS_H__*/
