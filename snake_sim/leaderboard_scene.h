/**
 * leaderboard_scene.h
 * 
 * Scene where the leaderboard table can be accesed/reset
 * 
 * The leaderboard is always sorted descending by the highscore
 * 
 * Current state of the leaderboard is stored in a file defined in constants.h as LEADERBOARD_FILE
 * Default state of the leaderboard is stored in a file defined in constants.h as LEADERBOARD_DEF_FILE\
 * 
 * created by Vit Soumar and Marek Jirku for computer architectures course semestral project
*/


#ifndef __LEADERBOARD_SCENE_H__
#define __LEADERBOARD_SCENE_H__


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "scene_t.h"
#include "utils.h"
#include "global_values.h"
#include "button_t.h"
#include "table_t.h"
#include "leaderboard_utils.h"
#include "constants.h"
#include "theme_utils.h"
#include "mzapo_utils.h"

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"


#define MEM_ALLOC_ERROR_LDBRD 106

//table format
#define TABLE_X 50
#define TABLE_Y 100

#define CELL_W 127
#define CELL_H 22

#define CELL_TEXT_SCALE 1
#define TABLE_BORDER_SIZE 1

//button size
#define LDBRD_BUTTON_W 170
#define LDBRD_BUTTON_H 40

//anchor button pos - other buttons pos is relative to this one
#define LDBRD_ANCHOR_BUTTON_X 50
#define LDBRD_ANCHOR_BUTTON_Y 250

//button spacing
#define LDBRD_BUTTONS_SPACING_X 40


/**
 * initialize the scene
*/
scene_t* create_leaderboard();

/**
 * initialize scene display buffer
 * fill it with background color
 * add static text that will not change during the scene run time
*/
void init_leaderboard(scene_t* scene);

/**
 * add all buttons, variable text etc to the screen display buffer]
 * 
 * run the scene:
 * -handle input
 * -update scene display buffer
 * -refresh real screen
 * -free all memory on exit
 * 
 * returns: number of following scene
*/
int update_leaderboard(scene_t* scene);

/**
 * frees scene display buffer
*/
void exit_leaderboard(scene_t* scene);

#endif /*__LEADERBOARD_SCENE_H__*/
