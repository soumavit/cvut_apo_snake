#include "options_scene.h"

enum menu_b_enum{SNAKE_SIZE_B, SNAKE_SPEED_B, SNAKE1_COLOR_B, SNAKE2_COLOR_B, FRUIT_COLOR_B, THEME_B, BACK_B, DEFAULT_B};


void set_options_buttons(button_group_t* button_group, opt_button_group_t* opt_button_group);
void save_options(opt_button_group_t* obg);
void load_default_options(opt_button_group_t* bg);
void load_current_options(opt_button_group_t* bg);
void change_scene_theme(unsigned int** buffer, button_group_t* bg, opt_button_group_t* obg);


scene_t* create_options(){
    scene_t* scene = malloc(sizeof(scene_t));
    if (!scene){
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(MEM_ALLOC_ERROR_OPT);
    }

    scene->init = init_options;
    scene->update = update_options;
    scene->exit = exit_options;

    return scene;
}

void init_options(scene_t* scene) {
    //set leds to ambient
    set_leds(10, 10, 10);
    reset_ledline();

    scene->buffer = init_scene_buffer(WIDTH, HEIGHT);
    set_background(scene->buffer, WIDTH, HEIGHT, PRIMARY_COLOR);

    int header_center = center_text_x(0, WIDTH, "Options", SCENE_HEADER_SIZE);
    draw_string(scene->buffer, header_center, SCENE_HEADER_Y, "Options", SECONDARY_COLOR, SCENE_HEADER_SIZE);

}

int update_options(scene_t* scene) {
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = REFRESH_USEC};
    my_sleep(loop_delay);

    button_group_t* button_group = button_group_init(8);
    opt_button_group_t* opt_button_group = opt_button_group_init(6);
    set_options_buttons(button_group, opt_button_group);
    
    draw_buttons(scene->buffer, button_group);
    draw_opt_buttons(scene->buffer, opt_button_group);

    //input handling
    knobs_t* knobs_new = knobs_init();
    knobs_t* knobs_old = knobs_init();

    //load current state of knobs to both structs
    update_input(knobs_new);
    update_input(knobs_old);

    while (1){
        my_sleep(loop_delay);
        refresh_display(scene->buffer);

        update_input(knobs_new);

        int red_knob = get_input_red(knobs_new, knobs_old);
        int green_knob = get_input_green(knobs_new, knobs_old);


        //LEFT BUTTONS
        if (red_knob < 0){
            if (button_group->selected_button != 0 && button_group->selected_button != -1){
                select_button(button_group, --button_group->selected_button);
                draw_buttons(scene->buffer, button_group);
                update_input(knobs_old);
            }
        }

        if (red_knob > 0){
            if (button_group->selected_button != (button_group->num_of_buttons - 1) && button_group->selected_button != -1){
                select_button(button_group, ++button_group->selected_button);
                draw_buttons(scene->buffer, button_group);
                update_input(knobs_old);
            }
        }

        if (get_press_red(knobs_new)){

            int selected_button = button_group->selected_button;

            switch (selected_button)
            {
            case SNAKE_SIZE_B:
            case SNAKE_SPEED_B:
            case THEME_B:
                select_button(button_group, -1);
                select_opt_button(opt_button_group, selected_button);
                break;

            case SNAKE1_COLOR_B:
            case SNAKE2_COLOR_B:
            case FRUIT_COLOR_B:
                select_button(button_group, -1);
                select_opt_button(opt_button_group, selected_button);

                uint8_t r, g, b;
                int selected_label_idx = opt_button_group->buttons[opt_button_group->selected_button]->current_label_idx;
                rgb565_to_rgb(opt_button_group->buttons[selected_button]->label_values[selected_label_idx], &r, &g, &b);
                set_leds(r,g,b);
                break;

            case BACK_B:
                save_options(opt_button_group);
                free_all_buttons(button_group);
                free_all_opt_buttons(opt_button_group);
                free(knobs_new);
                free(knobs_old);
                return MAIN_MENU_S;

            case DEFAULT_B:
                load_default_options(opt_button_group);
                set_all_default(opt_button_group);
                change_scene_theme(scene->buffer, button_group, opt_button_group);
                select_button(button_group, 0);
                break;
            default:
                continue;
            }

            draw_buttons(scene->buffer, button_group);
            draw_opt_buttons(scene->buffer, opt_button_group);
            continue;
        }


        //RIGHT BUTTONS (WITH OPTIONS)
        if (green_knob < 0){
            if (opt_button_group->selected_button != -1){
                minus_label(opt_button_group->buttons[opt_button_group->selected_button]);

                //visual effects
                uint8_t r, g, b;
                int selected_label_idx = opt_button_group->buttons[opt_button_group->selected_button]->current_label_idx;
                int selected_button = opt_button_group->selected_button;
                switch(opt_button_group->selected_button){
                    //handle change of theme
                    case THEME_B:
                        change_scene_theme(scene->buffer, button_group, opt_button_group);
                        draw_buttons(scene->buffer, button_group);
                        break;
                    //set led colors depending on the current color setting
                    case SNAKE1_COLOR_B:
                    case SNAKE2_COLOR_B:
                    case FRUIT_COLOR_B:
                        rgb565_to_rgb(opt_button_group->buttons[selected_button]->label_values[selected_label_idx], &r, &g, &b);
                        set_leds(r,g,b);
                        break;
                }

                draw_opt_buttons(scene->buffer, opt_button_group);
                update_input(knobs_old);
            }
        }

        if (green_knob > 0){
            if (opt_button_group->selected_button != -1){
                plus_label(opt_button_group->buttons[opt_button_group->selected_button]);

                uint8_t r, g, b;
                int selected_label_idx = opt_button_group->buttons[opt_button_group->selected_button]->current_label_idx;
                int selected_button = opt_button_group->selected_button;
                switch(opt_button_group->selected_button){
                    //handle change of theme
                    case THEME_B:
                        change_scene_theme(scene->buffer, button_group, opt_button_group);
                        draw_buttons(scene->buffer, button_group);
                        break;
                    //set led colors depending on the current color setting
                    case SNAKE1_COLOR_B:
                    case SNAKE2_COLOR_B:
                    case FRUIT_COLOR_B:
                        rgb565_to_rgb(opt_button_group->buttons[selected_button]->label_values[selected_label_idx], &r, &g, &b);
                        set_leds(r,g,b);
                        break;
                }

                draw_opt_buttons(scene->buffer, opt_button_group);
                update_input(knobs_old);
            }
        }

        if (get_press_green(knobs_new)){
            //set leds back to ambient mode
            set_leds(10,10,10);

            int selected_button = opt_button_group->selected_button;

            if (selected_button != -1){
                select_opt_button(opt_button_group, -1);
                select_button(button_group, selected_button);
            }   

            draw_buttons(scene->buffer, button_group);
            draw_opt_buttons(scene->buffer, opt_button_group);
            continue;
        }
    }
    return SCENE_SWITCH_ERROR;
}


void exit_options(scene_t* scene){
    free_scene_buffer(scene->buffer, HEIGHT);
}

/**
 * for each option button it saves the currently selected label (option) to 
 * the variables defined in global_values.h
*/
void save_options(opt_button_group_t* obg){
    SNAKE_SPEED = obg->buttons[SNAKE_SPEED_B]->label_values[obg->buttons[SNAKE_SPEED_B]->current_label_idx];
    TILE_SIZE = obg->buttons[SNAKE_SIZE_B]->label_values[obg->buttons[SNAKE_SIZE_B]->current_label_idx];
    SNAKE1_COLOR = obg->buttons[SNAKE1_COLOR_B]->label_values[obg->buttons[SNAKE1_COLOR_B]->current_label_idx];
    SNAKE2_COLOR = obg->buttons[SNAKE2_COLOR_B]->label_values[obg->buttons[SNAKE2_COLOR_B]->current_label_idx];
    FRUIT_COLOR = obg->buttons[FRUIT_COLOR_B]->label_values[obg->buttons[FRUIT_COLOR_B]->current_label_idx];
    THEME = obg->buttons[THEME_B]->label_values[obg->buttons[THEME_B]->current_label_idx];
}

/**
 * create all buttons in this scene (both normal buttons and buttons with more options)
 * for each option button add all needed labels and values
 * set colors for both normal and option buttons
*/
void set_options_buttons(button_group_t* button_group, opt_button_group_t* opt_button_group){
    int buttons_x = OPTIONS_ANCHOR_BUTTON_X; // center would be -> WIDTH/2 - OPTIONS_BUTTON_W/2;
    int buttons_y = OPTIONS_ANCHOR_BUTTON_Y;

    int opt_buttons_x = buttons_x + OPTIONS_BUTTON_W + OPTIONS_BUTTONS_SPACING_X;
    int y_spacing = OPTIONS_BUTTONS_SPACING_Y;

    button_t* snake_size_b = button_init(buttons_x, buttons_y, OPTIONS_BUTTON_W, OPTIONS_BUTTON_H, "Snake size", TEXT_1, BORDER_1);
    opt_button_t* snake_size_ob = opt_button_init(opt_buttons_x, buttons_y, OPTIONS_BUTTON_W, OPTIONS_BUTTON_H, 5, TEXT_1, BORDER_1);
    add_label(snake_size_ob, "5px", 5);
    add_label(snake_size_ob, "10px", 10);
    add_label(snake_size_ob, "15px", 15);
    add_label(snake_size_ob, "20px", 20);
    add_label(snake_size_ob, "30px", 30);

    buttons_y += snake_size_b->height + y_spacing;

    button_t* snake_speed_b = button_init(buttons_x, buttons_y, OPTIONS_BUTTON_W, OPTIONS_BUTTON_H, "Snake speed", TEXT_1, BORDER_1);
    opt_button_t* snake_speed_ob = opt_button_init(opt_buttons_x, buttons_y, OPTIONS_BUTTON_W, OPTIONS_BUTTON_H, 5, TEXT_1, BORDER_1);
    add_label(snake_speed_ob, "1", 1);
    add_label(snake_speed_ob, "2", 2);
    add_label(snake_speed_ob, "3", 3);
    add_label(snake_speed_ob, "4", 4);
    add_label(snake_speed_ob, "5", 5);

    buttons_y += snake_speed_b->height + y_spacing;

    button_t* snake1_color_b = button_init(buttons_x, buttons_y, OPTIONS_BUTTON_W, OPTIONS_BUTTON_H, "Snake 1 color", TEXT_1, BORDER_1);
    opt_button_t* snake1_color_ob = opt_button_init(opt_buttons_x, buttons_y, OPTIONS_BUTTON_W, OPTIONS_BUTTON_H, 8, TEXT_1, BORDER_1);
    add_label(snake1_color_ob, "PINK", PINK);
    add_label(snake1_color_ob, "RED", RED);
    add_label(snake1_color_ob, "ORANGE", ORANGE);
    add_label(snake1_color_ob, "YELLOW", YELLOW);
    add_label(snake1_color_ob, "LIME", LIME);
    add_label(snake1_color_ob, "GREEN", GREEN);
    add_label(snake1_color_ob, "CYAN", CYAN);
    add_label(snake1_color_ob, "BLUE", BLUE);

    buttons_y += snake1_color_b->height + y_spacing;

    button_t* snake2_color_b = button_init(buttons_x, buttons_y, OPTIONS_BUTTON_W, OPTIONS_BUTTON_H, "Snake 2 color", TEXT_1, BORDER_1);
    opt_button_t* snake2_color_ob = opt_button_init(opt_buttons_x, buttons_y, OPTIONS_BUTTON_W, OPTIONS_BUTTON_H, 8, TEXT_1, BORDER_1);
    add_label(snake2_color_ob, "PINK", PINK);
    add_label(snake2_color_ob, "RED", RED);
    add_label(snake2_color_ob, "ORANGE", ORANGE);
    add_label(snake2_color_ob, "YELLOW", YELLOW);
    add_label(snake2_color_ob, "LIME", LIME);
    add_label(snake2_color_ob, "GREEN", GREEN);
    add_label(snake2_color_ob, "CYAN", CYAN);
    add_label(snake2_color_ob, "BLUE", BLUE);

    buttons_y += snake2_color_b->height + y_spacing;

    button_t* fruit_color_b = button_init(buttons_x, buttons_y, OPTIONS_BUTTON_W, OPTIONS_BUTTON_H, "Fruit color", TEXT_1, BORDER_1);
    opt_button_t* fruit_color_ob = opt_button_init(opt_buttons_x, buttons_y, OPTIONS_BUTTON_W, OPTIONS_BUTTON_H, 8, TEXT_1, BORDER_1);
    add_label(fruit_color_ob, "PINK", PINK);
    add_label(fruit_color_ob, "RED", RED);
    add_label(fruit_color_ob, "ORANGE", ORANGE);
    add_label(fruit_color_ob, "YELLOW", YELLOW);
    add_label(fruit_color_ob, "LIME", LIME);
    add_label(fruit_color_ob, "GREEN", GREEN);
    add_label(fruit_color_ob, "CYAN", CYAN);
    add_label(fruit_color_ob, "BLUE", BLUE);

    buttons_y += snake2_color_b->height + y_spacing;
    button_t* theme_b = button_init(buttons_x, buttons_y, OPTIONS_BUTTON_W, OPTIONS_BUTTON_H, "Color theme", TEXT_1, BORDER_1);
    opt_button_t* theme_ob = opt_button_init(opt_buttons_x, buttons_y, OPTIONS_BUTTON_W, OPTIONS_BUTTON_H, 3, TEXT_1, BORDER_1);
    add_label(theme_ob, "CLASSIC THEME", CLASSIC_THEME);
    add_label(theme_ob, "LIGHT THEME", LIGHT_THEME);
    add_label(theme_ob, "DARK THEME", DARK_THEME);

    buttons_y += fruit_color_b->height + y_spacing * 3;

    button_t* back_b = button_init(buttons_x, buttons_y, OPTIONS_BUTTON_W, OPTIONS_BUTTON_H, "Save", TEXT_1, BORDER_1);
    button_t* default_b = button_init(opt_buttons_x, buttons_y, OPTIONS_BUTTON_W, OPTIONS_BUTTON_H, "Default", TEXT_1, BORDER_1);
    buttons_y += back_b->height + y_spacing;

    button_group->buttons[SNAKE_SIZE_B] = snake_size_b;
    button_group->buttons[SNAKE_SPEED_B] = snake_speed_b;
    button_group->buttons[SNAKE1_COLOR_B] = snake1_color_b;
    button_group->buttons[SNAKE2_COLOR_B] = snake2_color_b;
    button_group->buttons[FRUIT_COLOR_B] = fruit_color_b;
    button_group->buttons[THEME_B] = theme_b;
    button_group->buttons[BACK_B] = back_b;
    button_group->buttons[DEFAULT_B] = default_b;

    opt_button_group->buttons[SNAKE_SIZE_B] = snake_size_ob;
    opt_button_group->buttons[SNAKE_SPEED_B] = snake_speed_ob;
    opt_button_group->buttons[SNAKE1_COLOR_B] = snake1_color_ob;
    opt_button_group->buttons[SNAKE2_COLOR_B] = snake2_color_ob;
    opt_button_group->buttons[FRUIT_COLOR_B] = fruit_color_ob;
    opt_button_group->buttons[THEME_B] = theme_ob;

    load_default_options(opt_button_group);
    load_current_options(opt_button_group);

    set_buttons_colors(button_group, PRIMARY_COLOR, SECONDARY_COLOR);
    set_option_buttons_colors(opt_button_group, PRIMARY_COLOR, SECONDARY_COLOR);
    select_button(button_group, 0);
}

/**
 * for each option button it sets its default value to whatever value is set as default in global_values.h
*/
void load_default_options(opt_button_group_t* bg){
    for (int i = 0; i < bg->buttons[SNAKE_SIZE_B]->used_labels_cap; i++){
        if (DEF_TILE_SIZE == bg->buttons[SNAKE_SIZE_B]->label_values[i]){
            bg->buttons[SNAKE_SIZE_B]->def_label_idx = i;
        }
    }

    for (int i = 0; i < bg->buttons[SNAKE_SPEED_B]->used_labels_cap; i++){
        if (DEF_SNAKE_SPEED == bg->buttons[SNAKE_SPEED_B]->label_values[i]){
            bg->buttons[SNAKE_SPEED_B]->def_label_idx = i;
        }
    }

    for (int i = 0; i < bg->buttons[SNAKE1_COLOR_B]->used_labels_cap; i++){
        if (DEF_SNAKE1_COLOR == bg->buttons[SNAKE1_COLOR_B]->label_values[i]){
            bg->buttons[SNAKE1_COLOR_B]->def_label_idx = i;
        }
    }

    for (int i = 0; i < bg->buttons[SNAKE2_COLOR_B]->used_labels_cap; i++){
        if (DEF_SNAKE2_COLOR == bg->buttons[SNAKE2_COLOR_B]->label_values[i]){
            bg->buttons[SNAKE2_COLOR_B]->def_label_idx = i;
        }
    }

    for (int i = 0; i < bg->buttons[FRUIT_COLOR_B]->used_labels_cap; i++){
        if (DEF_FRUIT_COLOR == bg->buttons[FRUIT_COLOR_B]->label_values[i]){
            bg->buttons[FRUIT_COLOR_B]->def_label_idx = i;
        }
    }

    for (int i = 0; i < bg->buttons[THEME_B]->used_labels_cap; i++){
        if (DEF_THEME == bg->buttons[THEME_B]->label_values[i]){
            bg->buttons[THEME_B]->def_label_idx = i;
        }
    }
    set_all_default(bg);
}

/**
 * for each option button it sets its label to whatever value is currently set in the options scene 
 * (the real values are stored in global_values.c)
*/
void load_current_options(opt_button_group_t* bg){
    for (int i = 0; i < bg->buttons[SNAKE_SIZE_B]->used_labels_cap; i++){
        if (TILE_SIZE == bg->buttons[SNAKE_SIZE_B]->label_values[i]){
            set_active_label(bg->buttons[SNAKE_SIZE_B], i);
        }
    }

    for (int i = 0; i < bg->buttons[SNAKE_SPEED_B]->used_labels_cap; i++){
        if (SNAKE_SPEED == bg->buttons[SNAKE_SPEED_B]->label_values[i]){
            set_active_label(bg->buttons[SNAKE_SPEED_B], i);
        }
    }

    for (int i = 0; i < bg->buttons[SNAKE1_COLOR_B]->used_labels_cap; i++){
        if (SNAKE1_COLOR == bg->buttons[SNAKE1_COLOR_B]->label_values[i]){
            set_active_label(bg->buttons[SNAKE1_COLOR_B], i);
        }
    }

    for (int i = 0; i < bg->buttons[SNAKE2_COLOR_B]->used_labels_cap; i++){
        if (SNAKE2_COLOR == bg->buttons[SNAKE2_COLOR_B]->label_values[i]){
            set_active_label(bg->buttons[SNAKE2_COLOR_B], i);
        }
    }

    for (int i = 0; i < bg->buttons[FRUIT_COLOR_B]->used_labels_cap; i++){
        if (FRUIT_COLOR == bg->buttons[FRUIT_COLOR_B]->label_values[i]){
            set_active_label(bg->buttons[FRUIT_COLOR_B], i);
        }
    }

    for (int i = 0; i < bg->buttons[THEME_B]->used_labels_cap; i++){
        if (THEME == bg->buttons[THEME_B]->label_values[i]){
            set_active_label(bg->buttons[THEME_B], i);
        }
    }
}


/**
 * changes the theme of the scene without reloading the whole scene
*/
void change_scene_theme(unsigned int** buffer, button_group_t* bg, opt_button_group_t* obg){
    THEME = obg->buttons[THEME_B]->label_values[obg->buttons[THEME_B]->current_label_idx];
    set_theme();

    //fill screen with background color
    set_background(buffer, WIDTH, HEIGHT, PRIMARY_COLOR);

    //draw logo in new color
    int header_center = center_text_x(0, WIDTH, "Options", SCENE_HEADER_SIZE);
    draw_string(buffer, header_center, SCENE_HEADER_Y, "Options", SECONDARY_COLOR, SCENE_HEADER_SIZE);

    //set button collors
    set_buttons_colors(bg, PRIMARY_COLOR, SECONDARY_COLOR);
    set_option_buttons_colors(obg, PRIMARY_COLOR, SECONDARY_COLOR);

    //redraw buttons in new colors
    draw_buttons(buffer, bg);
    draw_opt_buttons(buffer, obg);
}
