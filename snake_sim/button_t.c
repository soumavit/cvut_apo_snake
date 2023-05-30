#include "button_t.h"


int calc_label_x(int x, int w, char* s, int scale);
int calc_label_y(int y, int h, char* s, int scale);


button_t* button_init(int x, int y, int width, int height, char* label, int label_size, int border_size){
    button_t* button = malloc(sizeof(button_t));
    if (!button){
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(MEM_ALLOC_ERROR_BUTTON);
    }

    button->x = x;
    button->y = y;
    button->width = width;
    button->height = height;

    button->is_selected = false;

    button->label = label;
    button->border_size = border_size;

    button->label_size = label_size;
    button->label_x = calc_label_x(button->x, button->width, button->label, button->label_size);
    button->label_y = calc_label_y(button->y, button->height, button->label, button->label_size);;

    //next values are set to defaul, it can be changed later directly
    button->color = B_DEF_COLOR;
    button->selected_color = B_DEF_SELECTED_COLOR;

    button->label_color = B_DEF_LABEL_COLOR;
    button->selected_label_color = B_DEF_SELECTED_LABEL_COLOR;

    button->border_color = B_DEF_BORDER_COLOR;
    button->selected_border_color = B_DEF_SELECTED_BORDER_COLOR;
    return button;
}


button_group_t* button_group_init(int n){
    button_group_t* btg = malloc(sizeof(button_group_t));
    if (!btg){
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(MEM_ALLOC_ERROR_BUTTON);
    }

    btg->buttons = malloc(sizeof(button_t*) * n);
    if (!btg->buttons){
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(MEM_ALLOC_ERROR_BUTTON);
    }

    btg->num_of_buttons = n;
    btg->selected_button = -1;

    return btg;
}


void free_all_buttons(button_group_t* bg){
    for (int i = 0; i < bg->num_of_buttons; i++){
        free(bg->buttons[i]);
    }

    free(bg->buttons);
    free(bg);
}


void select_button(button_group_t* bg, int idx){
    if (bg->selected_button == -1){
        bg->selected_button = idx;
        bg->buttons[bg->selected_button]->is_selected = true;
        return;
    }
    bg->buttons[bg->selected_button]->is_selected = false;
    bg->selected_button = idx;
    if (idx != -1){
        bg->buttons[bg->selected_button]->is_selected = true;
    }   
}


void draw_button(unsigned int** buffer, button_t* b){
    //draw the rectangle without border
    for (int r = b->border_size; r < b->height - b->border_size; r++){
        for (int s = b->border_size; s < b->width - b->border_size; s++){
            draw_pixel(buffer, b->x+s, b->y+r, b->color);
        }
    }

    //draw border
    for (int r = 0; r < b->border_size; r++){
        for (int s = 0; s < b->width; s++){
            draw_pixel(buffer, b->x+s, b->y+r, b->border_color);
        }
    }

    for (int r = b->border_size; r < b->height - b->border_size; r++){
        for (int s = 0; s < b->border_size; s++){
            draw_pixel(buffer, b->x+s, b->y+r, b->border_color);
        }
        for (int s = b->width - b->border_size; s < b->width; s++){
            draw_pixel(buffer, b->x+s, b->y+r, b->border_color);
        }

    }

    for (int r = b->height-b->border_size; r < b->height; r++){
        for (int s = 0; s < b->width; s++){
            draw_pixel(buffer, b->x+s, b->y+r, b->border_color);
        }
    }

    //draw the text
    draw_string(buffer, b->label_x, b->label_y, b->label, b->label_color, b->label_size);

}


void draw_selected_button(unsigned int** buffer, button_t* b){
    //draw the rectangle
    for (int r = 0; r < b->height; r++){
        for (int s = 0; s < b->width; s++){
            draw_pixel(buffer, b->x+s, b->y+r, b->selected_color);
        }
    }

    //draw border
    for (int r = 0; r < b->border_size; r++){
        for (int s = 0; s < b->width; s++){
            draw_pixel(buffer, b->x+s, b->y+r, b->selected_border_color);
        }
    }

    for (int r = b->border_size; r < b->height - b->border_size; r++){
        for (int s = 0; s < b->border_size; s++){
            draw_pixel(buffer, b->x+s, b->y+r, b->selected_border_color);
        }
        for (int s = b->width - b->border_size; s < b->width; s++){
            draw_pixel(buffer, b->x+s, b->y+r, b->selected_border_color);
        }

    }

    for (int r = b->height-b->border_size; r < b->height; r++){
        for (int s = 0; s < b->width; s++){
            draw_pixel(buffer, b->x+s, b->y+r, b->selected_border_color);
        }
    }

    //draw the text
    draw_string(buffer, b->label_x, b->label_y, b->label, b->selected_label_color, b->label_size);

}


void draw_buttons(unsigned int** buffer, button_group_t* bg){
    for (int i = 0; i < bg->num_of_buttons; i++){
        if (i == bg->selected_button){
            draw_selected_button(buffer, bg->buttons[i]);
        } else {
            draw_button(buffer, bg->buttons[i]);
        }
    }
}


int calc_label_x(int x, int w, char* s, int scale){
    int s_w = string_width(s) * scale;
    int offset = x + (w - s_w)/2;
    return offset;
}


int calc_label_y(int y, int h, char* s, int scale){
    int s_h = DEF_CHAR_HEIGHT * scale;
    int offset = y + (h - s_h)/2;
    return offset;
}
