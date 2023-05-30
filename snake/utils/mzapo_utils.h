/**
 * mzapo_utils.h
 * 
 * This file contains functions that control the physical aspects of MicroZed APO
 * the device for which this app has been designed for
 * 
 * Created by Vit Soumar and Marek Jirku for computer architectures course semestral project
*/


#ifndef __MZAPO_UTILS_H__
#define __MZAPO_UTILS_H__


#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "constants.h"
#include "global_values.h"

#include "micro_zed_files/mzapo_parlcd.h"
#include "micro_zed_files/mzapo_phys.h"
#include "micro_zed_files/mzapo_regs.h"


/**
 * holds information about the state of red, green and blue knob on the mzapo board
*/
typedef struct knobs_t{
    uint8_t r;
    uint8_t g;
    uint8_t b;

    bool r_pressed;
    bool g_pressed;
    bool b_pressed;
}knobs_t;

/**
 * sleeps for delay.tv_usec nanoseconds
*/
void my_sleep(struct timespec delay);

/**
 * creates and return a pointer to knob struct
*/
knobs_t* knobs_init(void);

/**
 * updates the info stored in the struct to current state of the knobs
*/
void update_input(knobs_t* knobs);

/**
 * returns > 0 if new red knob value is > than old red knob value (if the red knob has been rotated to the right)
 * returns < 0 if new red knob value is < than old red knob value (if the red knob has been rotated to the left)
 * returns 0 if the red value stored in both of the knob structs is the same (the red knob has remained the same)
*/
int get_input_red(knobs_t *new, knobs_t* old);

/**
 * returns > 0 if new green knob value is > than old green knob value (if the green knob has been rotated to the right)
 * returns < 0 if new green knob value is < than old green knob value (if the green knob has been rotated to the left)
 * returns 0 if the green value stored in both of the knob structs is the same (the green knob has remained the same)
*/
int get_input_green(knobs_t* new, knobs_t* old);

/**
 * returns > 0 if new blue knob value is > than old blue knob value (if the blue knob has been rotated to the right)
 * returns < 0 if new blue knob value is < than old blue knob value (if the blue knob has been rotated to the left)
 * returns 0 if the blue value stored in both of the knob structs is the same (the blue knob has remained the same)
*/
int get_input_blue(knobs_t* new, knobs_t* old);

/**
 * returns true if the red knob has been pressed, false otherwise
*/
bool get_press_red(knobs_t* knobs);

/**
 * returns true if the green knob has been pressed, false otherwises
*/
bool get_press_green(knobs_t* knobs);

/**
 * returns true if the blueknob has been pressed, false otherwises
*/
bool get_press_blue(knobs_t* knobs);

/**
 * sets led1 to the r g b color
*/
void set_led1(uint8_t r, uint8_t g, uint8_t b);

/**
 * sets led2 to the r g b color
*/
void set_led2(uint8_t r, uint8_t g, uint8_t b);

/**
 * sets both leds to the r g b color
*/
void set_leds(uint8_t r, uint8_t g, uint8_t b);

/*
* sets on the led light from ledline on index idx
*/
void set_ledline_on(int *led_strip, int idx);

/**
 * sets off the led light from ledline on index idx
*/
void set_ledline_off(int *led_strip, int idx);

/**
 * turns off the whole ledline
*/
void reset_ledline();

/**
 * turn on the whole ledline
*/
void fill_ledline();

/**
 * ledline effect 1
*/
void led_effect1();

/**
 * ledline effect 2
*/
void led_effect2();

/**
 * ledline effect for when the snake dies
*/
void led_effect_game_over();

/**
 * displays the content of **buffer to the actual mzapo display
*/
void refresh_display(unsigned int **buffer);

#endif /*__MZAPO_UTILS_H__*/
