#include "option_button_t.h"

#define OB_DEF_LABEL_COLOR 2
#define OB_DEF_SELECTED_LABEL_COLOR 1

#define OB_DEF_COLOR 1
#define OB_DEF_SELECTED_COLOR 2
#define OB_DEF_BORDER_COLOR 2
#define OB_DEF_SELECTED_BORDER_COLOR 1


int calc_opt_label_x(int x, int w, char* s, int scale);
int calc_opt_label_y(int y, int h, char* s, int scale);


opt_button_t* opt_button_init(int x, int y, int width, int height, int num_of_labels, int label_size, int border_size){
    opt_button_t* button = malloc(sizeof(opt_button_t));
    if (!button){
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(MEM_ALLOC_ERROR);
    }

    button->x = x;
    button->y = y;
    button->width = width;
    button->height = height;

    button->is_selected = false;

    button->labels_cap = num_of_labels;
    button->used_labels_cap = 0;

    button->labels = malloc(sizeof(char*) * num_of_labels);
    if (!button->labels){
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(MEM_ALLOC_ERROR);
    }

    button->label_values = malloc(sizeof(int) * num_of_labels);
    if (!button->label_values){
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(MEM_ALLOC_ERROR);
    }
    button->def_label_idx = 0;
    button->current_label_idx = -1;

    //next values are set to defaul, it can be changed later directly
    button->label_size = label_size;

    button->color = OB_DEF_COLOR;
    button->selected_color = OB_DEF_SELECTED_COLOR;

    button->label_color = OB_DEF_LABEL_COLOR;
    button->selected_label_color = OB_DEF_SELECTED_LABEL_COLOR;

    button->border_color = OB_DEF_BORDER_COLOR;
    button->selected_border_color = OB_DEF_SELECTED_BORDER_COLOR;

    button->border_size = border_size;//change

    return button;
}


opt_button_group_t* opt_button_group_init(int n){
    opt_button_group_t* btg = malloc(sizeof(opt_button_group_t));
    if (!btg){
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(MEM_ALLOC_ERROR);
    }

    btg->buttons = malloc(sizeof(opt_button_t*) * n);
    if (!btg->buttons){
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(MEM_ALLOC_ERROR);
    }

    btg->num_of_buttons = n;
    btg->selected_button = -1;

    return btg;
}


void free_all_opt_buttons(opt_button_group_t* bg){
    for (int i = 0; i < bg->num_of_buttons; i++){
        free(bg->buttons[i]->labels);
        free(bg->buttons[i]->label_values);
        free(bg->buttons[i]);
    }
    free(bg->buttons);
    free(bg);
}


void add_label(opt_button_t* b, char* label, int value){
    if (b->used_labels_cap != b->labels_cap){
        b->labels[b->used_labels_cap] = label;
        b->label_values[b->used_labels_cap] = value;
        b->used_labels_cap++;

        if (b->current_label_idx == -1){
            b->current_label_idx = 0;
            b->label = b->labels[b->current_label_idx];
            b->label_x = calc_opt_label_x(b->x, b->width, b->label, b->label_size);
            b->label_y = calc_opt_label_y(b->y, b->height, b->label, b->label_size);
        }
    }
}


void plus_label(opt_button_t* b){
    if (b->current_label_idx != b->labels_cap-1){
        b->current_label_idx++;
        b->label = b->labels[b->current_label_idx];
        b->label_x = calc_opt_label_x(b->x, b->width, b->label, b->label_size);
        b->label_y = calc_opt_label_y(b->y, b->height, b->label, b->label_size);
    }
}


void minus_label(opt_button_t* b){
    if (b->current_label_idx != 0){
        b->current_label_idx--;
        b->label = b->labels[b->current_label_idx];
        b->label_x = calc_opt_label_x(b->x, b->width, b->label, b->label_size);
        b->label_y = calc_opt_label_y(b->y, b->height, b->label, b->label_size);
    } 
}


void set_active_label(opt_button_t* b, int idx){
    b->current_label_idx = idx;
    b->label = b->labels[b->current_label_idx];
    b->label_x = calc_opt_label_x(b->x, b->width, b->label, b->label_size);
    b->label_y = calc_opt_label_y(b->y, b->height, b->label, b->label_size);
}


void select_opt_button(opt_button_group_t* bg, int idx){
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


void draw_opt_button(unsigned int** buffer, opt_button_t* b){
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

void draw_selected_opt_button(unsigned int** buffer, opt_button_t* b){
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


void draw_opt_buttons(unsigned int** buffer, opt_button_group_t* bg){
    for (int i = 0; i < bg->num_of_buttons; i++){
        if (i == bg->selected_button){
            draw_selected_opt_button(buffer, bg->buttons[i]);
        } else {
            draw_opt_button(buffer, bg->buttons[i]);
        }
    }
}


void set_default_label(opt_button_t* b){
    b->current_label_idx = b->def_label_idx;
    b->label = b->labels[b->def_label_idx];
    b->label_x = calc_opt_label_x(b->x, b->width, b->label, b->label_size);
    b->label_y = calc_opt_label_y(b->y, b->height, b->label, b->label_size);
}


void set_all_default(opt_button_group_t* obg){
    for (int i = 0; i < obg->num_of_buttons; i++){
        set_default_label(obg->buttons[i]);
    }
}


int calc_opt_label_x(int x, int w, char* s, int scale){
    int s_w = string_width(s) * scale;
    int offset = x + (w - s_w)/2;
    return offset;
}


int calc_opt_label_y(int y, int h, char* s, int scale){
    int s_h = DEF_CHAR_HEIGHT * scale;
    int offset = y + (h - s_h)/2;
    return offset;
}
