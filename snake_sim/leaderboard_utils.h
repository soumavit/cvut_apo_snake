/**
 * leaderboard_utils.h
 * 
 * Defines leaderboard_t struct that stores info about the leaderboard table
 * 
 * Contains functions to draw the leaderboard to display buffer
 * Constains functions to update, reset, and save the leaderboard
 * 
 * created by Vit Soumar and Marek Jirku for computer architectures course semestral project
 * 
*/


#ifndef __LEADERBOARD_UTILS_H__
#define __LEADERBOARD_UTILS_H__


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "table_t.h"
#include "button_t.h"
#include "constants.h"


#define MEM_ALLOC_ERROR_LEADERBOARD 202

#define POS_COL 0
#define PLAYER_COL 1
#define SCORE_COL 2


/**
 * holds information about the leaderboard table
 * such as the position, size, border size and the buttons from which the leaderboard is created from
*/
typedef struct leaderboard_t{
    table_t* table;
    int x;
    int y;
    int w;
    int h;
    int border_size;
    button_group_t* bg;
} leaderboard_t;

/**
 * intitialize the leaderboard_t struct and retunr pointer to it
*/
leaderboard_t* leaderboard_init(char* filename, int x, int y, int cell_w, int cell_h, int text_size, int border_size);

/**
 * draw the leaderboard table to the display buffer
*/
void draw_leaderboard_table(unsigned int **buffer, leaderboard_t* l);

/**
 * free all alocated memory for the leaderboard_t struct
*/
void free_leaderboard_table(leaderboard_t* l);

/**
 * updates the table stored in file "filename" with new highscore of the player
*/
void update_leaderboard_table(char* filename, int player, int score);

/**
 * sorts the positions of the playes in the table t
*/
void sort_leaderboard_table_by_score(table_t* t);

/**
 * loads default table from the LEADERBOARD_DEF_FILE (defined in constants.h) and 
 * then stores it to the LEADERBOARD_FILE (defined in constanrs.h)
*/
void reset_leaderboard_table();

/**
 * function to sort an array ascending
*/
void sort_array_ascending(int* a, int n);

/**
 * function to sort an array descending
*/
void sort_array_descending(int* a, int n);

#endif /*__LEADERBOARD_UTILS_H__*/
