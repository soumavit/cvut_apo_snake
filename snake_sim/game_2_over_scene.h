/**
 * game_2_over_scene.h
 * 
 * Scene that gets displayed when one of the players dies in 2 player mode
 * 
 * created by Vit Soumar and Marek Jirku for computer architectures course semestral project
*/


#ifndef __GAME_2_OVER_SCENE_H__
#define __GAME_2_OVER_SCENE_H__


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "scene_t.h"
#include "utils.h"
#include "global_values.h"
#include "constants.h"
#include "button_t.h"
#include "theme_utils.h"
#include "mzapo_utils.h"

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"


#define MEM_ALLOC_ERROR_GAME2OVER 105

//button size
#define GO2_BUTTON_W 190
#define GO2_BUTTON_H 40

//anchor button pos - other buttons pos is relative to this one
#define GO2_ANCHOR_BUTTON_X 40
#define GO2_ANCHOR_BUTTON_Y 250

//button spacing
#define GO2_BUTTONS_SPACING_X 20


/**
 * initialize the scene
*/
scene_t* create_game_2_over();

/**
 * initialize scene display buffer
 * fill it with background color
 * add static text that will not change during the scene run time
*/
void init_game_2_over(scene_t* scene);

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
int update_game_2_over(scene_t* scene);

/**
 * frees scene display buffer
*/
void exit_game_2_over(scene_t* scene);

#endif /*__GAME_2_OVER_SCENE_H__*/
