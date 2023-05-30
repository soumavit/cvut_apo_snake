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

#include "scene_t.h"
#include "utils.h"
#include "global_values.h"
#include "button_t.h"
#include "theme_utils.h"
#include "mzapo_utils.h"

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"


#define MEM_ALLOC_ERROR_MENU 101

//button size
#define MENU_BUTTON_W 190
#define MENU_BUTTON_H 35

//anchor button pos - other buttons pos is relative to this one
#define MENU_ANCHOR_BUTTON_Y 110

//button spacing
#define MENU_BUTTONS_SPACING_Y 4


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
