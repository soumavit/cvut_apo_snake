#ifndef __MZAPO_UTILS_H__
#define __MZAPO_UTILS_H__

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>
#include <time.h>
#include "constants.h"
#include "global_values.h"

#define MEM_ALLOC_ERROR_SIMUTILS 300

#define WHITE 1
#define BLACK 2
#define CYAN 3
#define BLUE 4
#define YELLOW 5
#define RED 6
#define MAGENTA 7
#define GREEN 8

int kbhit(void);
void refresh_display(unsigned int** buffer);


#define MEM_ALLOC_ERROR_KNOBS 204

#define SKIP_HIGH 250
#define SKIP_LOW 10
#define STEP 1

typedef struct knobs_t{
    uint8_t r;
    uint8_t g;
    uint8_t b;

    bool r_pressed;
    bool g_pressed;
    bool b_pressed;
}knobs_t;

/**
 * basically just usleep
*/
void my_sleep(struct timespec delay);

knobs_t* knobs_init();
void update_input(knobs_t* knobs);

int get_input_red(knobs_t* new, knobs_t* old);
int get_input_green(knobs_t* new, knobs_t* old);
int get_input_blue(knobs_t* new, knobs_t* old);

bool get_press_red(knobs_t* knobs);
bool get_press_green(knobs_t* knobs);
bool get_press_blue(knobs_t* knobs);

void set_led1(uint8_t r, uint8_t g, uint8_t b);
void set_led2(uint8_t r, uint8_t g, uint8_t b);
void set_leds(uint8_t r, uint8_t g, uint8_t b);

void set_ledline_on(int *led_strip, int idx);
void set_ledline_off(int *led_strip, int idx);

void reset_ledline();
void fill_ledline();
void led_effect1();
void led_effect2();

void led_effect_game_over();


char** display_init();
void free_display(unsigned int** display);

#endif