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

#include "constants.h"
#include "global_values.h"

#include "types/scene_t.h"
#include "types/button_t.h"
#include "types/option_button_t.h"
#include "types/table_t.h"

#include "utils/utils.h"
#include "utils/leaderboard_utils.h"
#include "utils/theme_utils.h"
#include "utils/mzapo_utils.h"


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
