#include "main_menu_scene.h"

enum menu_b_enum{GAME1_B, GAME2_B, LEADERBOARD_B, OPTIONS_B, EXIT_B};


void set_menu_buttons(button_group_t* button_group);

scene_t* create_main_menu(){
    scene_t* scene = malloc(sizeof(scene_t));
    if (!scene){
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(MEM_ALLOC_ERROR_MENU);
    }

    scene->init = init_main_menu;
    scene->update = update_main_menu;
    scene->exit = exit_main_menu;

    return scene;
}


void init_main_menu(scene_t* scene) {
    //set leds to ambient mode
    set_leds(10, 10, 10);
    reset_ledline();

    scene->buffer = init_scene_buffer(WIDTH, HEIGHT);
    //fill screen background color
    set_background(scene->buffer, WIDTH, HEIGHT, PRIMARY_COLOR);

    //draw static text
    int header_center = center_text_x(0, WIDTH, "Main menu", SCENE_HEADER_SIZE);
    draw_string(scene->buffer, header_center, SCENE_HEADER_Y, "Main menu", SECONDARY_COLOR, SCENE_HEADER_SIZE);
}


int update_main_menu(scene_t* scene) {
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = REFRESH_USEC};
    struct timespec stop_delay = {.tv_sec = 0, .tv_nsec = REFRESH_USEC};

    my_sleep(stop_delay);

    button_group_t* button_group = button_group_init(5);
    set_menu_buttons(button_group);
    
    draw_buttons(scene->buffer, button_group);
    refresh_display(scene->buffer);

    //handle input
    knobs_t* knobs_new = knobs_init();
    knobs_t* knobs_old = knobs_init();

    update_input(knobs_new);
    update_input(knobs_old);

    while(1){
        my_sleep(loop_delay);
        update_input(knobs_new);

        //handle red knob
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
            case GAME1_B:
                return CHOOSE_PLAYER_S;
            case GAME2_B:
                return GAME2_S;
            case LEADERBOARD_B:
                return LEADERBOARD_S;
            case OPTIONS_B:
                return OPTIONS_S;
            case EXIT_B:
                return EXIT_GAME;
            default:
                return MAIN_MENU_S;
            }
        }
    }
    return SCENE_SWITCH_ERROR;
}


void exit_main_menu(scene_t* scene){
    free_scene_buffer(scene->buffer, HEIGHT);
}

/**
 * creates and sets colors for buttons used in this scene
 * every button is added to the button_group
*/
void set_menu_buttons(button_group_t* button_group){
    int buttons_x = WIDTH/2 - MENU_BUTTON_W/2;
    int buttons_y = MENU_ANCHOR_BUTTON_Y;
    int b_spacing = MENU_BUTTONS_SPACING_Y;

    button_t* play1_b = button_init(buttons_x, buttons_y, MENU_BUTTON_W, MENU_BUTTON_H, "1 player", TEXT_1, BORDER_1);
    buttons_y += play1_b->height + b_spacing;

    button_t* play2_b = button_init(buttons_x, buttons_y, MENU_BUTTON_W, MENU_BUTTON_H, "2 players", TEXT_1, BORDER_1);
    buttons_y += play2_b->height + b_spacing;

    button_t* leaderboard_b = button_init(buttons_x, buttons_y, MENU_BUTTON_W, MENU_BUTTON_H, "Leaderboard", TEXT_1, BORDER_1);
    buttons_y += leaderboard_b->height + b_spacing;

    button_t* options_b = button_init(buttons_x, buttons_y, MENU_BUTTON_W, MENU_BUTTON_H, "Options", TEXT_1, BORDER_1);
    buttons_y += options_b->height + b_spacing;

    button_t* exit_b = button_init(buttons_x, buttons_y, MENU_BUTTON_W, MENU_BUTTON_H, "Exit", TEXT_1, BORDER_1);

    button_group->buttons[GAME1_B] = play1_b;
    button_group->buttons[GAME2_B] = play2_b;
    button_group->buttons[LEADERBOARD_B] = leaderboard_b;
    button_group->buttons[OPTIONS_B] = options_b;
    button_group->buttons[EXIT_B] = exit_b;

    select_button(button_group, 0);
    set_buttons_colors(button_group, PRIMARY_COLOR, SECONDARY_COLOR);
}
