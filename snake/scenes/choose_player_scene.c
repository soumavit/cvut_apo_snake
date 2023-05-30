#include "choose_player_scene.h"

//button size
#define CHP_BUTTON_W 170
#define CHP_BUTTON_H 30

//anchor button pos - other buttons pos is relative to this one
#define CHP_ANCHOR_BUTTON_X 50
#define CHP_ANCHOR_BUTTON_Y 264

//button spacing
#define CHP_BUTTONS_SPACING_X 40

//CHOOSE PLAYER BUTTON
//main button pos 
#define CHP_MAIN_BUTTON_Y 115

//main button size
#define CHP_MAIN_BUTTON_W 230
#define CHP_MAIN_BUTTON_H 60

enum choose_player_b_enum{BACK_B, PLAY_B};
enum choose_player_ob_enum{PLAYER_OB, SCORE_OB};


void set_choose_player_buttons(button_group_t* button_group, opt_button_group_t* opt_button_group);


scene_t* create_choose_player(){
    scene_t* scene = malloc(sizeof(scene_t));
    if (!scene){
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(MEM_ALLOC_ERROR);
    }

    scene->init = init_choose_player;
    scene->update = update_choose_player;
    scene->exit = exit_choose_player;

    return scene;
}


void init_choose_player(scene_t* scene) {
    //set leds to ambient mode
    set_leds(10, 10, 10);
    reset_ledline();
    
    scene->buffer = init_scene_buffer(WIDTH, HEIGHT);
    set_background(scene->buffer, WIDTH, HEIGHT, PRIMARY_COLOR);

    //draw static text to the buffer
    int header_center = center_text_x(0, WIDTH, "Choose player", SCENE_HEADER_SIZE);
    draw_string(scene->buffer, header_center, SCENE_HEADER_Y, "Choose player", SECONDARY_COLOR, SCENE_HEADER_SIZE);
}


int update_choose_player(scene_t* scene) {
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = REFRESH_USEC};
    my_sleep(loop_delay);

    //set the buttons for the scene
    button_group_t* button_group = button_group_init(2);
    opt_button_group_t* opt_button_group = opt_button_group_init(2);
    set_choose_player_buttons(button_group, opt_button_group);

    //draw scene (active part) on the display
    draw_buttons(scene->buffer, button_group);
    draw_opt_buttons(scene->buffer, opt_button_group);
    refresh_display(scene->buffer);

    //create knob structs for input
    knobs_t* knobs_new = knobs_init();
    knobs_t* knobs_old = knobs_init();

    //load current state of knobs into the structs
    update_input(knobs_new);
    update_input(knobs_old);

    while(1){
        my_sleep(loop_delay);
        update_input(knobs_new);

        int red_knob = get_input_red(knobs_new, knobs_old);
        int green_knob = get_input_green(knobs_new, knobs_old);

        //handle red knob
        if (red_knob < 0){
            if (button_group->selected_button != 0 && button_group->selected_button !=-1){
                select_button(button_group, --button_group->selected_button);
                draw_buttons(scene->buffer, button_group);
                update_input(knobs_old);
            }
            else if (button_group->selected_button == 0){
                select_button(button_group, -1);
                select_opt_button(opt_button_group, PLAYER_OB);
                draw_buttons(scene->buffer, button_group);
                draw_opt_buttons(scene->buffer, opt_button_group);
                update_input(knobs_old);
            }
            refresh_display(scene->buffer);
        }

        if (red_knob > 0){
            if (button_group->selected_button != (button_group->num_of_buttons - 1) && button_group->selected_button !=-1){
                select_button(button_group, ++button_group->selected_button);
                draw_buttons(scene->buffer, button_group);
                refresh_display(scene->buffer);
                update_input(knobs_old);
            }
        }

        if (get_press_red(knobs_new)){
            switch (button_group->selected_button)
            {
            case BACK_B:
                free_all_buttons(button_group);
                free_all_opt_buttons(opt_button_group);
                free(knobs_new);
                free(knobs_old);
                return MAIN_MENU_S;
            case PLAY_B:
                CURRENT_PLAYER = opt_button_group->buttons[PLAYER_OB]->label_values[opt_button_group->buttons[PLAYER_OB]->current_label_idx];
                free_all_buttons(button_group);
                free_all_opt_buttons(opt_button_group);
                free(knobs_new);
                free(knobs_old);
                return GAME_S;
            default:
                break;
            }
        }

        //handle green knob (PLAYER CHOOSE BUTTON)
        if (green_knob < 0){
            if (opt_button_group->selected_button != -1){
                minus_label(opt_button_group->buttons[PLAYER_OB]);
                minus_label(opt_button_group->buttons[SCORE_OB]);
                draw_opt_buttons(scene->buffer, opt_button_group);
                refresh_display(scene->buffer);
                update_input(knobs_old);
            }
        }

        if (green_knob > 0){
            if (opt_button_group->selected_button != -1){
                plus_label(opt_button_group->buttons[PLAYER_OB]);
                plus_label(opt_button_group->buttons[SCORE_OB]);
                draw_opt_buttons(scene->buffer, opt_button_group);
                refresh_display(scene->buffer);
                update_input(knobs_old);
            }
        }

        if (get_press_green(knobs_new)){
            switch (opt_button_group->selected_button)
            {
            case PLAYER_OB:
                select_opt_button(opt_button_group, -1);
                select_button(button_group, PLAY_B);
                draw_buttons(scene->buffer, button_group);
                draw_opt_buttons(scene->buffer, opt_button_group);
                refresh_display(scene->buffer);
                continue;
            default:
                break;
            }
        }
    }
    return -1;
}


void exit_choose_player(scene_t* scene){
    free_scene_buffer(scene->buffer, HEIGHT);
}


void set_choose_player_buttons(button_group_t* button_group, opt_button_group_t* opt_button_group){
    int buttons_x = CHP_ANCHOR_BUTTON_X;
    int buttons_y = CHP_ANCHOR_BUTTON_Y;
    int spacing_x = CHP_BUTTONS_SPACING_X;

    //center
    int main_x = (WIDTH - CHP_MAIN_BUTTON_W) / 2;

    //button with players
    opt_button_t* player_ob = opt_button_init(main_x, CHP_MAIN_BUTTON_Y, CHP_MAIN_BUTTON_W, CHP_MAIN_BUTTON_H, 6, TEXT_2, BORDER_1);
    add_label(player_ob, "Player_1", PLAYER_1);
    add_label(player_ob, "Player_2", PLAYER_2);
    add_label(player_ob, "Player_3", PLAYER_3);
    add_label(player_ob, "Player_4", PLAYER_4);
    add_label(player_ob, "Player_5", PLAYER_5); 
    add_label(player_ob, "Player_6", PLAYER_6);
    
    //button with highscores
    table_t* scores = load_table_from_file(LEADERBOARD_FILE);
    opt_button_t* score_ob = opt_button_init(main_x, CHP_MAIN_BUTTON_Y+CHP_MAIN_BUTTON_H, CHP_MAIN_BUTTON_W, CHP_MAIN_BUTTON_H, 6, TEXT_2, NO_BORDER);
    for (int i = 0; i < 6; i++){
        add_label(score_ob, scores->cells[i][SCORE_COL]->displayed_text, scores->cells[i][SCORE_COL]->value);
    }

    opt_button_group->buttons[PLAYER_OB] = player_ob;
    opt_button_group->buttons[SCORE_OB] = score_ob;

    //back and continue button
    button_t* back_b = button_init(buttons_x, buttons_y, CHP_BUTTON_W, CHP_BUTTON_H, "Back", TEXT_1, BORDER_1);
    buttons_x += back_b->width + spacing_x;
    button_t* play_b = button_init(buttons_x, buttons_y, CHP_BUTTON_W, CHP_BUTTON_H, "Save and play", TEXT_1, BORDER_1);

    button_group->buttons[BACK_B] = back_b;
    button_group->buttons[PLAY_B] = play_b;

    select_opt_button(opt_button_group, 0);
    select_button(button_group, 0);
    select_button(button_group, -1);

    set_buttons_colors(button_group, PRIMARY_COLOR, SECONDARY_COLOR);
    set_option_buttons_colors(opt_button_group, PRIMARY_COLOR, SECONDARY_COLOR);

    free_table(scores);
}
