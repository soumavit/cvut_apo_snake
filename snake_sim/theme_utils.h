/**
 * theme_utils.h
 * 
 * This file contains functions to change/set the app theme
 * set theme function sets the overall app theme
 * set_background funciton set the color of background to mathc the current theme
 * and button functions set the colors of buttons to match the current theme
 * 
 * created by Vit Soumar and Marek Jirku for computer architectures course semestral project
*/


#ifndef __THEME_UTILS_H__
#define __THEME_UTILS_H_


#include "global_values.h"
#include "button_t.h"
#include "option_button_t.h"
#include "constants.h"


/**
 * sets PRIMARY, SECONDARY, GAME_BACKGROUND, SNAKE_BORDER colors
 * depending on the THEME (all defined in global_values.h)
*/
void set_theme();

/**
 * sets all of the elements of **buffer to background_color
*/
void set_background(unsigned int** buffer, int w, int h, unsigned int background_color);

/**
 * for all buttons from the button group their colors are changed to the current 
 * primary and secondary colors
*/
void set_buttons_colors(button_group_t* bg, unsigned int primary, unsigned int secondary);

/**
 * for all buttons from the button group their colors are changed to the current 
 * primary and secondary colors
*/
void set_option_buttons_colors(opt_button_group_t* bg, unsigned int primary, unsigned int secondary);

#endif /*__THEME_UTILS_H__*/
