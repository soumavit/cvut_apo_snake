/**
 * utils.h
 * 
 * This file contains all kind of functions, but mostly the functions that have something to do 
 * with drawing stuff to display buffer 
 * 
 * (!not really showing it on the real display, just storing it in the display buffer array, which can be later 
 * shown on the real diplay!)
 * 
 * Also contains color converison functions
 * Also contains functions that can draw ppm image to display buffer
 * 
 * Created by Vit Soumar for computer architectures course semestral project
*/


#ifndef __UTILS_H__
#define __UTILS_H__


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "constants.h"
#include "font_types.h"
#include "global_values.h"
#include "option_button_t.h"
#include "button_t.h"


#define FILE_ERROR 500
#define MEM_ALLOC_ERROR_UTILS 200


/**
 * draw on single pixel of color to the display buffer
*/
void draw_pixel(unsigned int **buffer, int x, int y, unsigned int color);

/**
 * draw scaled pixel to the display buffer
*/
void draw_pixel_scaled(unsigned int **buffer, int x, int y, unsigned int color, int scale);

/**
 * helper function
 * calculates the width of char ch
*/
int char_width(int ch);

/**
 * helper function
 * calculates the width of the string s
 * calculates width of each char and adds it together
 * the width depend on used chars in the string
 * 
*/
int string_width(char* s);

/**
 * draw scaled char c to the display buffer to pos x, y with color color
*/
void draw_char(unsigned int **buffer, int x, int y, char c, unsigned int color, int scale);

/**
 * draw scaled string s to the display buffer to pos x, y with color color
*/
void draw_string(unsigned int **buffer, int x, int y, char* s, unsigned int color, int scale);

/**
 * calculates x coordinate using the with of the string and width of the space where the text will be displayed at
*/
int center_text_x(int x, int w, char* s, int scale);

/**
 * calculates y coordinate using the height of the string and height of the space where the text will be displayed at
*/
int center_text_y(int y, int h, char* s, int scale);

/**
 * loads ppm from file
 * returns the file as a unsigned int*
*/
unsigned int* load_ppm(int *width, int *height, const char* file);

/**
 * saves *image to file *file
*/
void save_ppm(unsigned int* image, int width, int height, char* file);

/**
 * initialize screen buffer with height h and width w
*/
unsigned int** init_scene_buffer(int w, int h);

/**
 * free scene screen buffer 2d array
*/
void free_scene_buffer(unsigned int** buffer, int h);
/**
 * converts 565 ocolor format to 888rgb format
*/
void rgb565_to_rgb(unsigned int color, uint8_t *r, uint8_t* g, uint8_t *b);

/**
 * converts 888 rgb to 565 color format
*/
unsigned int rgb_to_565(unsigned int r, unsigned int g, unsigned int b);

/**
 * converts ppm image stored as a unsigned int* to a unsigned int** array with calculated
 * 565 color format for each pixel
*/
unsigned int** ppm_to_565(unsigned int* image, int w, int h);

#endif /*__UTILS_H__*/
