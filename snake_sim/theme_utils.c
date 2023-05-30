#include "theme_utils.h"


void set_theme(){
    switch (THEME)
    {
    case CLASSIC_THEME:
        PRIMARY_COLOR = LIME;
        SECONDARY_COLOR = BLACK;
        GAME_BACKGROUND_COLOR = LIME;
        SNAKE_BORDER_COLOR = BLACK;
        break;
    case LIGHT_THEME:
        PRIMARY_COLOR = WHITE;
        SECONDARY_COLOR = BLACK;
        GAME_BACKGROUND_COLOR = WHITE;
        SNAKE_BORDER_COLOR = BLACK;
        break;
    case DARK_THEME:
        PRIMARY_COLOR = BLACK;
        SECONDARY_COLOR = WHITE;
        GAME_BACKGROUND_COLOR = BLACK;
        SNAKE_BORDER_COLOR = WHITE;
        break;
    default:
        break;
    }
}


void set_background(unsigned int** buffer, int w, int h, unsigned int background_color){
    for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++){
            buffer[i][j] = background_color;
        }
    } 
}


void set_buttons_colors(button_group_t* bg, unsigned int primary, unsigned int secondary){
    for (int i = 0; i < bg->num_of_buttons; i++){
        bg->buttons[i]->color = primary;
        bg->buttons[i]->selected_color = secondary;

        bg->buttons[i]->border_color = secondary;
        bg->buttons[i]->selected_border_color = secondary;

        bg->buttons[i]->label_color = secondary;
        bg->buttons[i]->selected_label_color = primary;
    }
}


void set_option_buttons_colors(opt_button_group_t* bg, unsigned int primary, unsigned int secondary){
    for (int i = 0; i < bg->num_of_buttons; i++){
        bg->buttons[i]->color = secondary;
        bg->buttons[i]->selected_color = primary;

        bg->buttons[i]->border_color = secondary;
        bg->buttons[i]->selected_border_color = secondary;

        bg->buttons[i]->label_color = primary;
        bg->buttons[i]->selected_label_color = secondary;
    }
}
