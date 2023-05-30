#include "loading_screen_scene.h"

#define STOP_DELAY 300000

//text positions
#define LOGO_Y 50
#define LOADING_TEXT_Y 240

//press any key text blinking speed
#define BLINKING_SPEED 5


void redraw_background_image(unsigned int** buffer, unsigned int** background);
void draw_loading_percent(unsigned int** buffer, int percent, unsigned int color);
void animate_loading(unsigned int** buffer, unsigned int** background);


scene_t* create_load_screen(){
    scene_t* scene = malloc(sizeof(scene_t));
    if (!scene){
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(MEM_ALLOC_ERROR);
    }

    scene->init = init_load_screen;
    scene->update = update_load_screen;
    scene->exit = exit_load_screen;

    return scene;
}


void init_load_screen(scene_t* scene) {
    scene->buffer = init_scene_buffer(WIDTH, HEIGHT);
}


int update_load_screen(scene_t* scene) {
    //turn off leds and ledline in case they were lit and not turned off
    set_leds(0, 0, 0);
    reset_ledline();


    //MZAPO
    int w = 0;
    int h = 0;
    unsigned int* image = load_ppm(&w, &h, LOGO_FILE);
    unsigned int** background = ppm_to_565(image, w, h);
    redraw_background_image(scene->buffer, background);
    refresh_display(background);

    //free(image);
    

    //SIM
    /*
    unsigned int ** background = init_scene_buffer(WIDTH, HEIGHT);
    set_background(background, WIDTH, HEIGHT, BLACK);
    */

    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = REFRESH_USEC};
    struct timespec stop_delay = {.tv_sec = 0, .tv_nsec = STOP_DELAY};
    my_sleep(loop_delay);

    //handle input
    knobs_t* knobs_new = knobs_init();
    knobs_t* knobs_old = knobs_init();

    update_input(knobs_new);
    update_input(knobs_old);

    //animate loading
    animate_loading(scene->buffer, background);

    //set led orange when loading is finished to match with the led strip
    set_leds(255, 20, 0);
    my_sleep(stop_delay);
    
    redraw_background_image(scene->buffer, background);
    refresh_display(scene->buffer);
    
    long int anim_counter = 0;

    while(1){
        my_sleep(loop_delay);
        refresh_display(scene->buffer);

        anim_counter++;
        int text_center = center_text_x(0, WIDTH, "Press any key to continue...", TEXT_2);
        if (anim_counter % (BLINKING_SPEED*2) < BLINKING_SPEED){
            draw_string(scene->buffer, text_center, LOADING_TEXT_Y, "Press any key to continue...", SECONDARY_COLOR, TEXT_2);
        } else {
            draw_string(scene->buffer, text_center, LOADING_TEXT_Y, "Press any key to continue...", PRIMARY_COLOR, TEXT_2);
        }

        //check input from all knobs
        update_input(knobs_new);
        if (get_input_red(knobs_new, knobs_old) || get_input_green(knobs_new, knobs_old) || get_input_blue(knobs_new, knobs_old)
            || get_press_red(knobs_new) || get_press_green(knobs_new) || get_press_blue(knobs_new))
            {
                free_scene_buffer(background, HEIGHT);
                free(knobs_new);
                free(knobs_old);
                return MAIN_MENU_S;
            }
        update_input(knobs_old);
    }
    
    return SCENE_SWITCH_ERROR;
}


void exit_load_screen(scene_t* scene){
    free_scene_buffer(scene->buffer, HEIGHT);
}


/**
 * copy the background image to the scene display buffer
*/
void redraw_background_image(unsigned int** buffer, unsigned int **background){
    for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++){
            buffer[i][j] = background[i][j];
        }
    }
}

/**
 * draw string with the loading process to the display buffer
*/
void draw_loading_percent(unsigned int** buffer, int percent, unsigned int color){

    char loading_text[25] = "LOADING ";
    char percent_s[5];
    char percent_c[5] = "\%";

    sprintf(percent_s, "%d", percent);
    strcat(percent_s, percent_c);

    strcat(loading_text, percent_s);
    
    int loading_center = center_text_x(0, WIDTH, loading_text, TEXT_2);
    draw_string(buffer, loading_center, LOADING_TEXT_Y, loading_text, color, TEXT_2);
}

/**
 * depending on the loading process, turn on the ledstrip lights and draw current
 * state of the loading process to the display buffer
*/
void animate_loading(unsigned int** buffer, unsigned int** background){
    time_t t;
    srand((unsigned) time(&t));
    int led_line = 0;

    for (int i = 31; i >= 0; i--){

        redraw_background_image(buffer, background);
        int percent = 100 - i*3;
        draw_loading_percent(buffer, percent, SECONDARY_COLOR);
        refresh_display(buffer);

        set_ledline_on(&led_line, i);
        int r = rand() % 100000; //*2
        usleep(r); 
        draw_loading_percent(buffer, percent, PRIMARY_COLOR);   
    }
    draw_loading_percent(buffer, 100, PRIMARY_COLOR);
    refresh_display(buffer);
}
