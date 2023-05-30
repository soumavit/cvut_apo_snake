/**
 * game_over_scene.h
 * 
 * Scene that gets displayed when the playe dies in 1 player mode
 * 
 * created by Vit Soumar and Marek Jirku for computer architectures course semestral project
*/

#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "scene_t.h"
#include "utils.h"
#include "global_values.h"
#include "constants.h"
#include "button_t.h"
#include "table_t.h"
#include "leaderboard_utils.h"
#include "theme_utils.h"
#include "mzapo_utils.h"

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"


#define MEM_ALLOC_ERROR_GAMEOVER 105

//button size
#define GO_BUTTON_W 120
#define GO_BUTTON_H 40

//anchor button pos - other buttons pos is relative to this one
#define GO_ANCHOR_BUTTON_X 40
#define GO_ANCHOR_BUTTON_Y 260

//button spacing
#define GO_BUTTONS_SPACING_X 20

//text pos
#define SCORE_TEXT_Y 165
#define HIGHSCORE_TEXT_Y 200


/**
 * initialize the scene
*/
scene_t* create_game_over();

/**
 * initialize scene display buffer
 * fill it with background color
 * add static text that will not change during the scene run time
*/
void init_game_over(scene_t* scene);

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
int update_game_over(scene_t* scene);

/**
 * frees scene display buffer
*/
void exit_game_over(scene_t* scene);

#endif /*__GAME_OVER_SCENE_H__*/
