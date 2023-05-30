#include "game_2_over_scene.h"

enum game_2_over_b_enum{PLAY_B, MENU_B};


void set_game_2_over_buttons(button_group_t* button_group);


scene_t* create_game_2_over(){
    scene_t* scene = malloc(sizeof(scene_t));
    if (!scene){
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(MEM_ALLOC_ERROR_GAME2OVER);
    }

    scene->init = init_game_2_over;
    scene->update = update_game_2_over;
    scene->exit = exit_game_2_over;

    return scene;
}


void init_game_2_over(scene_t* scene) {

    scene->buffer = init_scene_buffer(WIDTH, HEIGHT);
    //fill screen with background color
    set_background(scene->buffer, WIDTH, HEIGHT, PRIMARY_COLOR);

    //draw GAME OVER text
    int header_center = center_text_x(0, WIDTH, "GAME OVER", GAME_OVER);
    draw_string(scene->buffer, header_center, SCENE_HEADER_Y, "GAME OVER", SECONDARY_COLOR, GAME_OVER);
    
    //score of player 1
    char score1[20] = "Player 1 score: ";
    char score_num1[3];
    sprintf(score_num1, "%d", SCORE_PLAYER1);
    strcat(score1, score_num1);

    //score of player 2
    char score2[20] = "Player 2 score: ";
    char score_num2[3];
    sprintf(score_num2, "%d", SCORE_PLAYER2);
    strcat(score2, score_num2);

    //draw scores to the display buffer
    draw_string(scene->buffer, center_text_x(0, WIDTH, score1, TEXT_2), 130, score1, SNAKE1_COLOR, TEXT_2);
    draw_string(scene->buffer, center_text_x(0, WIDTH, score2, TEXT_2), 170, score2, SNAKE2_COLOR, TEXT_2);
}


int update_game_2_over(scene_t* scene) {

    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = REFRESH_USEC};
    my_sleep(loop_delay);

    button_group_t* button_group = button_group_init(2);
    set_game_2_over_buttons(button_group);
    draw_buttons(scene->buffer, button_group);

    knobs_t* knobs_new = knobs_init();
    knobs_t* knobs_old = knobs_init();

    update_input(knobs_new);
    update_input(knobs_old);

    refresh_display(scene->buffer);

    while(1){
        my_sleep(loop_delay);
        update_input(knobs_new);

        //handle input on red button
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
            SCORE_PLAYER1 = 0;
            SCORE_PLAYER2 = 0;

            switch (selected_button)
            {
            case PLAY_B:
                return GAME2_S;
            case MENU_B:
                return MAIN_MENU_S;
            default:
                return SCENE_SWITCH_ERROR;
            }
        }
    }
    return SCENE_SWITCH_ERROR;
}


void exit_game_2_over(scene_t* scene){
    free_scene_buffer(scene->buffer, HEIGHT);
}

/**
 * creates and sets colors for buttons used in this scene
 * every button is added to the button_group
*/
void set_game_2_over_buttons(button_group_t* button_group){
    int buttons_x = GO2_ANCHOR_BUTTON_X;
    int buttons_y = GO2_ANCHOR_BUTTON_Y;
    int spacing_x = GO2_BUTTONS_SPACING_X;
    
    button_t* play_b = button_init(buttons_x, buttons_y, GO2_BUTTON_W, GO2_BUTTON_H, "Play again", TEXT_1, BORDER_1);
    buttons_x = play_b->width + play_b->x + spacing_x;

    button_t* menu_b = button_init(buttons_x, buttons_y, GO2_BUTTON_W, GO2_BUTTON_H, "Main menu", TEXT_1, BORDER_1);

    button_group->buttons[PLAY_B] = play_b;
    button_group->buttons[MENU_B] = menu_b;

    select_button(button_group, 0);
    set_buttons_colors(button_group, PRIMARY_COLOR, SECONDARY_COLOR);
}
