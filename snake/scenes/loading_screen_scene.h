/**
 * loading_screen_scene.h
 * 
 * First scene that the user sees is this one
 * Obtains custom game logo aswell with some loading progress and text
 * 
 * The following scene after this one is Main menu
 * 
 * created by Vit Soumar and Marek Jirku for computer architectures course semestral project
*/


#ifndef __LOADING_SCREEN_SCENE_H__
#define __LOADING_SCREEN_SCENE_H__


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "constants.h"
#include "global_values.h"

#include "types/scene_t.h"

#include "utils/utils.h"
#include "utils/theme_utils.h"
#include "utils/mzapo_utils.h"


/**
 * initialize the scene
*/
scene_t* create_load_screen();

/**
 * initialize scene display buffer
 * fill it with background color
 * add static text that will not change during the scene run time
*/
void init_load_screen(scene_t* scene);

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
int update_load_screen(scene_t* scene);

/**
 * frees scene display buffer
*/
void exit_load_screen(scene_t* scene);

#endif /*__LOADING_SCREEN_SCENE_H__*/
