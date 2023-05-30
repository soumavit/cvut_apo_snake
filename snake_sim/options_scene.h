/**
 * options_scene.h
 * 
 * This scene obtains all the options that can be changed by the user
 * Currently, these are the options:
 *      Snake size
 *      Snake speed
 *      Snake1 color
 *      Snake2 color
 *      Fruit color
 *      App theme
 * 
 * All the options that the user can change have predefined list of values from which the user can choose from
 * 
 * created by Vit Soumar and Marek Jirku for computer architectures course semestral project
*/


#ifndef __OPTIONS_SCENE_H__
#define __OPTIONS_SCENE_H__


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "scene_t.h"
#include "utils.h"
#include "global_values.h"
#include "button_t.h"
#include "option_button_t.h"
#include "theme_utils.h"
#include "mzapo_utils.h"

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"


#define MEM_ALLOC_ERROR_OPT 107

//button size
#define OPTIONS_BUTTON_W 200
#define OPTIONS_BUTTON_H 25

//anchor button - other buttons pos is relative to this one
#define OPTIONS_ANCHOR_BUTTON_X 20
#define OPTIONS_ANCHOR_BUTTON_Y 100

//button spacing
#define OPTIONS_BUTTONS_SPACING_Y 3
#define OPTIONS_BUTTONS_SPACING_X 40


/**
 * initialize the scene
*/
scene_t* create_options();

/**
 * initialize scene display buffer
 * fill it with background color
 * add static text that will not change during the scene run time
*/
void init_options(scene_t* scene);

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
int update_options(scene_t* scene);

/**
 * frees scene display buffer
*/
void exit_options(scene_t* scene);

#endif /*__OPTIONS_SCENE_H__*/
