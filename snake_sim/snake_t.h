/**
 * snake_t.h
 * 
 * snake_t struct is defined here
 * tile_t struct is defined here (acts as a snake tile)
 * 
 * The functions defined here are used to update, enlarge and control the snake
 * This file is not capable of drawing the snake, its just a snake model
 * 
 * created by Vit Soumar and Marek Jirku for computer architectures course semestral project
 * 
*/

#ifndef __SNAKE_T_H__
#define __SNAKE_T_H__


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "constants.h"
#include "global_values.h"


#define MEM_ALLOC_ERROR_SNAKE 303


/**
 * this struct holds one snake tile, and the pointer to the previous and to the next snake tile
 * if there is either no next or prev tile, that pointer should be set to NULL
*/
typedef struct tile_t{
    int x;
    int y;
    struct tile_t* next;
    struct tile_t* prev;
} tile_t;

/**
 * this structure only holds information about the snake, the fruit the snake eats is not part of it
 * fruit is controlled by the game, thats why fruit_t is declared in game_utils and not here
 **/
typedef struct snake_t{
    tile_t* head;
    tile_t* tail;
    int size;
    int tile_size;
    int dir_x;
    int dir_y;
} snake_t;

/**
 * initialize the snake struct and returns a pointer to it
 * x, y initial position of the snake
 * tile size is the size of one snake tile
 * dir_x and dir_y is the initial direction of the snake
*/
snake_t* snake_init(int x, int y, int tile_size, int dir_x, int dir_y);

/**
 * initialize one tile and return a pointer to it
*/
tile_t* tile_init(int x, int y);

/**
 * sets the snakes direction
*/
void set_snake_dir(snake_t* s, int dir_x, int dir_y);

/**
 * updates the snake position
 * 
 * if enlarged == true, the whole snake doesnt move, just the head moves because one tile has
 * been added on the place of the head (using the enlarge function) -> this makes the snake one tile longer
 * 
 * if enlarged == false, the tail of the snake gets placed in front of the snakes 
 * head (depends on the snake direction), creating the effect of the snake moving
*/
void update_snake(snake_t* s, bool enlarged);

/**
 * a new tile gets inserted on the same position as the head
 * 
 * after enlarging, the update snake function should be calles with true as the second parameter
*/
void enlarge_snake(snake_t* s);

/**
 * free all memory allocated for the snake structure
*/
void delete_snake(snake_t* s);

#endif /*__SNAKE_T_H__*/
