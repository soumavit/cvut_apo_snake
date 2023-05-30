#include "game_over_scene.h"

//button size
#define GO_BUTTON_W 120
#define GO_BUTTON_H 40

//anchor button pos - other buttons pos is relative to this one
#define GO_ANCHOR_BUTTON_X 40
#define GO_ANCHOR_BUTTON_Y 260

//button spacing
#define GO_BUTTONS_SPACING_X 20

//text pos
#define SCORE_TEXT_Y 165
#define HIGHSCORE_TEXT_Y 200

enum game_over_b_enum{PLAY_B, MENU_B, LEADERBOARD_B};


void set_game_over_buttons(button_group_t* button_group);


scene_t* create_game_over(){
    scene_t* scene = malloc(sizeof(scene_t));
    if (!scene){
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(MEM_ALLOC_ERROR);
    }

    scene->init = init_game_over;
    scene->update = update_game_over;
    scene->exit = exit_game_over;

    return scene;
}


void init_game_over(scene_t* scene) {
    scene->buffer = init_scene_buffer(WIDTH, HEIGHT);
    set_background(scene->buffer, WIDTH, HEIGHT, PRIMARY_COLOR);

    //draw static text
    int header_center = center_text_x(0, WIDTH, "GAME OVER", GAME_OVER);
    draw_string(scene->buffer, header_center, SCENE_HEADER_Y, "GAME OVER", SECONDARY_COLOR, GAME_OVER);

    //load saved highscores from a file
    table_t *scores = load_table_from_file(LEADERBOARD_FILE);

    int score = SCORE;

    //load highscore for current player
    int highscore = scores->cells[CURRENT_PLAYER][SCORE_COL]->value;
    //create string with player name
    char* player = scores->cells[CURRENT_PLAYER][PLAYER_COL]->displayed_text;

    //create string with score
    char score_text[10] = "Score:";
    char score_num[10];
    sprintf(score_num, "%d", SCORE);
    strcat(score_text, score_num);

    //draw player name to the buffer
    draw_string(scene->buffer, center_text_x(0, WIDTH, player, TEXT_2), 120, player, SECONDARY_COLOR, TEXT_2);

    //draw score and highscore
    if (score > highscore){
        update_leaderboard_table(LEADERBOARD_FILE, CURRENT_PLAYER, score);
        draw_string(scene->buffer, center_text_x(0, WIDTH, "New highscore!", TEXT_2), SCORE_TEXT_Y, "New highscore!", SECONDARY_COLOR, TEXT_2);
        draw_string(scene->buffer, center_text_x(0, WIDTH, score_text, TEXT_2), HIGHSCORE_TEXT_Y, score_text, SECONDARY_COLOR, TEXT_2);
    } else{
        draw_string(scene->buffer, center_text_x(0, WIDTH, score_text, TEXT_2), SCORE_TEXT_Y, score_text, SECONDARY_COLOR, TEXT_2);
        draw_string(scene->buffer, center_text_x(0, WIDTH, scores->cells[CURRENT_PLAYER][SCORE_COL]->displayed_text, TEXT_2), HIGHSCORE_TEXT_Y, scores->cells[CURRENT_PLAYER][SCORE_COL]->displayed_text, SECONDARY_COLOR, TEXT_2);
    }

    free_table(scores);
}


int update_game_over(scene_t* scene) {
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = REFRESH_USEC};
    my_sleep(loop_delay);

    //create scene buttons
    button_group_t* button_group = button_group_init(3);
    set_game_over_buttons(button_group);
    draw_buttons(scene->buffer, button_group);

    //initialize knobs for input
    knobs_t* knobs_new = knobs_init();
    knobs_t* knobs_old = knobs_init();

    //load current state of knobs into the structs
    update_input(knobs_new);
    update_input(knobs_old);

    refresh_display(scene->buffer);

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
            SCORE = 0;

            switch (selected_button)
            {
            case PLAY_B:
                return GAME_S;
            case MENU_B:
                return MAIN_MENU_S;
            case LEADERBOARD_B:
                return LEADERBOARD_S;
            default:
                return SCENE_SWITCH_ERROR;
            }
        }

    }
    return SCENE_SWITCH_ERROR;
}


void exit_game_over(scene_t* scene){
    free_scene_buffer(scene->buffer, HEIGHT);
}


/**
 * creates and sets colors for buttons used in this scene
 * every button is added to the button_group
*/
void set_game_over_buttons(button_group_t* button_group){
    int buttons_x = GO_ANCHOR_BUTTON_X;
    int buttons_y = GO_ANCHOR_BUTTON_Y;
    int b_spacing = GO_BUTTONS_SPACING_X;
    
    button_t* play_b = button_init(buttons_x, buttons_y, GO_BUTTON_W, GO_BUTTON_H, "Play again", TEXT_1, BORDER_1);
    buttons_x = play_b->width + play_b->x + b_spacing;

    button_t* menu_b = button_init(buttons_x, buttons_y, GO_BUTTON_W, GO_BUTTON_H, "Main menu", TEXT_1, BORDER_1);
    buttons_x = menu_b->width + menu_b->x + b_spacing;

    button_t* leaderboard_b = button_init(buttons_x, buttons_y, GO_BUTTON_W, GO_BUTTON_H, "Leaderboard", TEXT_1, BORDER_1);

    button_group->buttons[PLAY_B] = play_b;
    button_group->buttons[MENU_B] = menu_b;
    button_group->buttons[LEADERBOARD_B] = leaderboard_b;

    select_button(button_group, 0);
    set_buttons_colors(button_group, PRIMARY_COLOR, SECONDARY_COLOR);
}
