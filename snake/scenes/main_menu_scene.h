/**
 * main_menu_scene.h
 * 
 * Main menu scene
 * This is the root scene of the app
 * Game modes for both 1 and 2 players can be accesed from here, options can be accesed from here
 * The user can also exit the app from here
 * 
 * created by Vit Soumar and Marek Jirku for computer architectures course semestral project
 * 
*/


#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "constants.h"
#include "global_values.h"

#include "types/scene_t.h"
#include "types/button_t.h"
#include "types/option_button_t.h"

#include "utils/utils.h"
#include "utils/theme_utils.h"
#include "utils/mzapo_utils.h"


/**
 * initialize the scene
*/
scene_t* create_main_menu();

/**
 * initialize scene display buffer
 * fill it with background color
 * add static text that will not change during the scene run time
*/
void init_main_menu(scene_t* scene);

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
int update_main_menu(scene_t* scene);

/**
 * frees scene display buffer
*/
void exit_main_menu(scene_t* scene);

#endif /*__MAIN_MENU_SCENE_H__*/
