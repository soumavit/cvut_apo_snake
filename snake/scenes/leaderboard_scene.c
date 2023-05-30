#include "leaderboard_scene.h"

//table format
#define TABLE_X 50
#define TABLE_Y 100

#define CELL_W 127
#define CELL_H 22

#define CELL_TEXT_SCALE 1
#define TABLE_BORDER_SIZE 1

//button size
#define LDBRD_BUTTON_W 170
#define LDBRD_BUTTON_H 40

//anchor button pos - other buttons pos is relative to this one
#define LDBRD_ANCHOR_BUTTON_X 50
#define LDBRD_ANCHOR_BUTTON_Y 250

//button spacing
#define LDBRD_BUTTONS_SPACING_X 40

enum leaderboard_b_enum{BACK_B, RESET_B};


void set_leaderboard_scene_buttons(button_group_t* button_group);


scene_t* create_leaderboard(){
    scene_t* scene = malloc(sizeof(scene_t));
    if (!scene){
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(MEM_ALLOC_ERROR);
    }

    scene->init = init_leaderboard;
    scene->update = update_leaderboard;
    scene->exit = exit_leaderboard;

    return scene;
}


void init_leaderboard(scene_t* scene) {
    //set leds to ambient mode
    set_leds(10, 10, 10);
    reset_ledline();

    scene->buffer = init_scene_buffer(WIDTH, HEIGHT);
    set_background(scene->buffer, WIDTH, HEIGHT, PRIMARY_COLOR);

    //draw static text
    int header_center = center_text_x(0, WIDTH, "Leaderboard", SCENE_HEADER_SIZE);
    draw_string(scene->buffer, header_center, SCENE_HEADER_Y, "Leaderboard", SECONDARY_COLOR, SCENE_HEADER_SIZE);

    //load leaderboard and draw it to scene display buffer 
    leaderboard_t* leaderboard = leaderboard_init(LEADERBOARD_FILE, TABLE_X, TABLE_Y, CELL_W, CELL_H, CELL_TEXT_SCALE, TABLE_BORDER_SIZE);
    set_buttons_colors(leaderboard->bg, PRIMARY_COLOR, SECONDARY_COLOR);
    draw_leaderboard_table(scene->buffer, leaderboard);
    free_leaderboard_table(leaderboard);
}


int update_leaderboard(scene_t* scene) {
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = REFRESH_USEC};
    my_sleep(loop_delay);

    //create scene buttons
    button_group_t* button_group = button_group_init(2);
    set_leaderboard_scene_buttons(button_group);
    draw_buttons(scene->buffer, button_group);

    refresh_display(scene->buffer);

    //create knobs for handling input
    knobs_t* knobs_new = knobs_init();
    knobs_t* knobs_old = knobs_init();

    update_input(knobs_new);
    update_input(knobs_old);

    while(1){
        my_sleep(loop_delay);

        //handle input
        update_input(knobs_new);
        int red_knob = get_input_red(knobs_new, knobs_old);

        if (red_knob < 0){
            if (button_group->selected_button != 0){
                select_button(button_group, --button_group->selected_button);
                draw_buttons(scene->buffer, button_group);
                refresh_display(scene->buffer);
                update_input(knobs_old);
            }
        }

        if (red_knob > 0){
            if (button_group->selected_button != (button_group->num_of_buttons - 1)){
                select_button(button_group, ++button_group->selected_button);
                draw_buttons(scene->buffer, button_group);
                refresh_display(scene->buffer);
                update_input(knobs_old);
            }
        }

        if (get_press_red(knobs_new)){
            int selected_button = button_group->selected_button;

            free_all_buttons(button_group);
            free(knobs_new);
            free(knobs_old);

            switch (selected_button)
            {
            case BACK_B:
                return MAIN_MENU_S;
            case RESET_B:
                reset_leaderboard_table();
                return LEADERBOARD_S;
            default:
                return SCENE_SWITCH_ERROR;
            }
        }
    }
    return SCENE_SWITCH_ERROR;
}


void exit_leaderboard(scene_t* scene){
    free_scene_buffer(scene->buffer, HEIGHT);
}

/**
 * creates and sets colors for buttons used in this scene
 * every button is added to the button_group
*/
void set_leaderboard_scene_buttons(button_group_t* button_group){
    int buttons_x = LDBRD_ANCHOR_BUTTON_X;
    int buttons_y = LDBRD_ANCHOR_BUTTON_Y;
    int b_spacing = LDBRD_BUTTONS_SPACING_X;

    button_t* back_b = button_init(buttons_x, buttons_y, LDBRD_BUTTON_W, LDBRD_BUTTON_H, "Main menu", TEXT_1, BORDER_1);
    buttons_x += back_b->width + b_spacing;

    button_t* reset_b = button_init(buttons_x, buttons_y, LDBRD_BUTTON_W, LDBRD_BUTTON_H, "Reset", TEXT_1, BORDER_1);

    button_group->buttons[BACK_B] = back_b;
    button_group->buttons[RESET_B] = reset_b;

    set_buttons_colors(button_group, PRIMARY_COLOR, SECONDARY_COLOR);
    select_button(button_group, 0);
}
