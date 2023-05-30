/**
 * button_t.h
 * 
 * Defines button_t struct and button_group_t type
 * Contains functions to create buttons and button group
 * Cnstains functions to draw the buttons to the display buffer
 * 
 * created by Vit Soumar and Marek Jirku for computer architectures course semestral project
*/


#ifndef __BUTTON_T_H__
#define __BUTTON_T_H__


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "global_values.h"
#include "constants.h"
#include "utils.h"


#define MEM_ALLOC_ERROR_BUTTON 300

#define B_DEF_LABEL_COLOR 2
#define B_DEF_SELECTED_LABEL_COLOR 1

#define B_DEF_COLOR 1
#define B_DEF_SELECTED_COLOR 2
#define B_DEF_BORDER_COLOR 2
#define B_DEF_SELECTED_BORDER_COLOR 1


/**
 * holds information about button
 * */
typedef struct button_t{
    int x;
    int y;
    int width;
    int height;

    char* label;
    int label_x;
    int label_y;
    int label_size;

    unsigned int color;
    unsigned int selected_color;

    unsigned int label_color;
    unsigned int selected_label_color;

    unsigned int border_color;
    unsigned int selected_border_color;

    int border_size;

    bool is_selected;
} button_t;

/**
 * struct for storing buttons in one group
 * manages which button is selected
*/
typedef struct button_group_t{
    int num_of_buttons;
    button_t** buttons;
    int selected_button;
} button_group_t;


/**
 * creates a button with set position, size, label and border size
 * other properties of the button are set to default
*/
button_t* button_init(int x, int y, int width, int height, char* label, int label_size, int border_size);

/**
 * creates a button group of n buttons
 * the buttons need to be added manualy
*/
button_group_t* button_group_init(int n);

/**
 * free all buttons in the button group (also frees the button group itself)
*/
void free_all_buttons(button_group_t* bg);

/**
 * select button in button group on index idx
*/
void select_button(button_group_t* bg, int idx);


/**
 * draw option button to the display buffer (buffer)
 * normal colors will be used
*/
void draw_button(unsigned int** buffer, button_t* b);

/**
 * draw option button to the display buffer (buffer)
 * selected colors will be used
*/
void draw_selected_button(unsigned int** buffer, button_t* b);

/**
 * draw all buttons from button group
 * the button on selected_button_index will be drawn as selected
*/
void draw_buttons(unsigned int** buffer, button_group_t* bg);

#endif /*__BUTTON_H__*/
