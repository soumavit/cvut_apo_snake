/**
 * game_scene.h
 * 
 * Scene obtaing the actual snake game mode for 1 player
 * 
 * created by Vit Soumar and Marek Jirku for computer architectures course semestral project
*/


#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "scene_t.h"
#include "constants.h"
#include "snake_t.h"
#include "utils.h"
#include "global_values.h"
#include "game_utils.h"
#include "button_t.h"
#include "theme_utils.h"
#include "mzapo_utils.h"

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"


#define MEM_ALLOC_ERROR_GAME 103

extern int GAME_WIDTH;
extern int GAME_HEIGHT;

/**
 * initialize the scene
*/
scene_t* create_game();

/**
 * initialize scene display buffer
 * fill it with game background color
*/
void init_game(scene_t* scene);

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
int update_game(scene_t* scene);

/**
 * frees scene display buffer
*/
void exit_game(scene_t* scene);

#endif /*__GAME_SCENE_H__*/
