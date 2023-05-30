/**
 * scene_t.h
 * 
 * scene_t struct is defined here
 * This struct is used for all app scenes
 * 
 * scene_manager_t struct is defined here
 * 
 * created by Vit Soumar and Marek Jirku for computer architectures course semestral project
*/


#ifndef __SCENE_T_H__
#define __SCENE_T_H__


#include <stdio.h>
#include <stdlib.h>
#include "constants.h"


/**
 * struct that holds a display buffer for the creen
 * 
 * pointer to the scenenes init function:
 *    initialize the scene display buffer and display
 *    static contents of the scene to the display
 * 
 * pointer to the scenes update function:
 *    update function constains a loop where the input is handled
 *    the display is updated according to the input by the user
 *    the function then returns number for the following scene
 * 
 * pointer to the scenes exit function
 *    the scenes display buffer is freed in this function
 * 
*/
typedef struct scene_t{
    unsigned int** buffer;
    void (*init)();
    int (*update)();
    void (*exit)();
} scene_t;

/**
 * hold all of the game scenes in one struct
*/
typedef struct scene_manager_t{
    scene_t** scene;
    int num_of_scenes;
} scene_manager_t;

/**
 * initialize and return a pointer to the scene manager struct
 * space for n scenes is allocated
 * scenes need to be added manualy later
*/
scene_manager_t* scene_man_init(int n);

/**
 * frees all scenes from the 
*/
void free_all_scenes(scene_manager_t* scn_m);

#endif /*__SCENE_T_H__*/
