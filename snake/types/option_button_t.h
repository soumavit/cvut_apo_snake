/**
 * option_button_t.h
 * 
 * Defines opt_button_t struct and opt_button_group_t type
 * Contains functions to create buttons with options (more labels) and group of option buttons
 * Cnstains functions to draw the buttons to the display buffer
 * 
 * created by Vit Soumar and Marek Jirku for computer architectures course semestral project
*/


#ifndef __OPTION_BUTTON_T_H__
#define __OPTION_BUTTON_T_H__


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "global_values.h"
#include "constants.h"
#include "utils/utils.h"


/**
 * holds information about the button with all its labels
 * */
typedef struct opt_button_t{
    int x;
    int y;
    int width;
    int height;

    int labels_cap;
    int used_labels_cap;

    char** labels;
    int* label_values;

    int def_label_idx;
    int current_label_idx;
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
} opt_button_t;

/**
 * struct for storing buttons in one group
 * manages which button is selected
*/
typedef struct opt_button_group_t{
    int num_of_buttons;
    opt_button_t** buttons;
    int selected_button;
} opt_button_group_t;


/**
 * creates an option button with position, size, number of labels (options), label and border size
 * other properties of the button are set to default
*/
opt_button_t* opt_button_init(int x, int y, int width, int height, int num_of_labels, int label_size, int border_size);

/**
 * creates a group of n option buttons
 * the buttons need to be added manualy
*/
opt_button_group_t* opt_button_group_init(int n);

/**
 * free all buttons in the button group (also frees the button group itself)
*/
void free_all_opt_buttons(opt_button_group_t* bg);

/**
 * adds new label (option) to button
 * if the whole button capacity is used, it will not be added
*/
void add_label(opt_button_t* b, char* label, int value);

/**
 * sets label on idx to active
*/
void set_active_label(opt_button_t* b, int idx);


/**
 * sets active the label to the right of the current active label
*/
void plus_label(opt_button_t* b);

/**
 * sets active the label to the left of the current active label
*/
void minus_label(opt_button_t* b);

/**
 * select button on idx from the button group of option buttons
*/
void select_opt_button(opt_button_group_t* bg, int idx);

/**
 * changes which label from the labels array is the default one
*/
void set_default_label(opt_button_t* b);

/**
 * set all buttons labels to the default label
*/
void set_all_default(opt_button_group_t* obg);


/**
 * draw option button to the display buffer (buffer)
 * only the curent label will be displayed
 * normal colors will be used
*/
void draw_opt_button(unsigned int** buffer, opt_button_t* b);

/**
 * draw option button to the display buffer (buffer)
 * only the curent label will be displayed
 * selected colors will be used
*/
void draw_selected_opt_button(unsigned int** buffer, opt_button_t* b);

/**
 * draw all options buttons from button group
 * the button on selected_button_index will be drawn as selected
 * only current labels of the buttons are drawn
*/
void draw_opt_buttons(unsigned int** buffer, opt_button_group_t* bg);

#endif /*__OPTION_BUTTON_T_H__*/
