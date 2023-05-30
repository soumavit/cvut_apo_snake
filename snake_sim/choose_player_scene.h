/**
 * choose_player_scene.h
 * 
 * Scene where the user chooses the player he wants to play as
 * Only for 1 player mode
 * 
 * created by Vit Soumar for computer architectures course semestral project
*/


#ifndef __CHOOSE_PLAYER_SCENE_H__
#define __CHOOSE_PLAYER_SCENE_H__


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "scene_t.h"
#include "utils.h"
#include "global_values.h"
#include "button_t.h"
#include "option_button_t.h"
#include "table_t.h"
#include "leaderboard_utils.h"
#include "theme_utils.h"
#include "constants.h"
#include "mzapo_utils.h"

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"


#define MEM_ALLOC_ERROR_CHOOSE_P 102

//button size
#define CHP_BUTTON_W 170
#define CHP_BUTTON_H 30

//anchor button pos - other buttons pos is relative to this one
#define CHP_ANCHOR_BUTTON_X 50
#define CHP_ANCHOR_BUTTON_Y 264

//button spacing
#define CHP_BUTTONS_SPACING_X 40

//CHOOSE PLAYER BUTTON
//main button pos 
#define CHP_MAIN_BUTTON_Y 115

//main button size
#define CHP_MAIN_BUTTON_W 230
#define CHP_MAIN_BUTTON_H 60


/**
 * initialize the scene
*/
scene_t* create_choose_player();

/**
 * initialize scene display buffer
 * fill it with background color
 * add static text that will not change during the scene run time
*/
void init_choose_player(scene_t* scene);

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
int update_choose_player(scene_t* scene);

/**
 * frees scene display buffer
*/
void exit_choose_player(scene_t* scene);

#endif /**__CHOOSE_PLAYER_SCENE_H__*/
