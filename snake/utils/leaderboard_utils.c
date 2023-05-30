#include "leaderboard_utils.h"


leaderboard_t* leaderboard_init(char* filename, int x, int y, int cell_w, int cell_h, int text_size, int border_size){
    leaderboard_t* l = malloc(sizeof(leaderboard_t));
    if (!l){
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(MEM_ALLOC_ERROR);
    }

    l->table = load_table_from_file(filename);
    l->border_size = border_size;

    l->x = x;
    l->y = y;

    l->h = cell_h * l->table->rows;
    l->w = cell_w * l->table->cols;

    l->bg = button_group_init(l->table->rows * l->table->cols);
    
    for (int r = 0; r < l->table->rows; r++){

        int button_y = l->y + l->table->cells[r][POS_COL]->value * cell_h;

        //position alone - the text has to be changed depending on position
        button_t* b;
        switch (l->table->cells[r][POS_COL]->value)
        {
        case 0:
            b = button_init(l->x + 0, button_y, cell_w, cell_h, "1st", text_size, 0);
            break;
        case 1:
            b = button_init(l->x + 0, button_y, cell_w, cell_h, "2nd", text_size, 0);
            break;
        case 2:
            b = button_init(l->x + 0, button_y, cell_w, cell_h, "3rd", text_size, 0);
            break;
        case 3:
            b = button_init(l->x + 0, button_y, cell_w, cell_h, "4th", text_size, 0);
            break;
        case 4:
            b = button_init(l->x + 0, button_y, cell_w, cell_h, "5th", text_size, 0);
            break;
        case 5:
            b = button_init(l->x + 0, button_y, cell_w, cell_h, "6th", text_size, 0);
            break;
        default:
            b = NULL;
            break;
        }
        l->bg->buttons[r*3] = b;


        for (int c = 1; c < l->table->cols; c++){
            button_t* bb = button_init(l->x + cell_w * c, button_y, cell_w, cell_h, l->table->cells[r][c]->displayed_text, text_size, 0);
            l->bg->buttons[r*3+c] = bb;
        }
    }    
    return l;
}


void draw_leaderboard_table(unsigned int **buffer, leaderboard_t* l){
    unsigned int border_color = l->bg->buttons[0]->border_color;

    draw_buttons(buffer, l->bg);
    //draw border
    for (int r = 0; r < l->border_size; r++){
        for (int s = 0; s < l->w; s++){
            draw_pixel(buffer, l->x+s, l->y+r, border_color);
        }
    }

    for (int r = l->border_size; r < l->h - l->border_size; r++){
        for (int s = 0; s < l->border_size; s++){
            draw_pixel(buffer, l->x+s, l->y+r, border_color);
        }
        for (int s = l->w - l->border_size; s < l->w; s++){
            draw_pixel(buffer, l->x+s, l->y+r, border_color);
        }

    }

    for (int r = l->h- l->border_size; r < l->h; r++){
        for (int s = 0; s < l->w; s++){
            draw_pixel(buffer, l->x+s, l->y+r, border_color);
        }
    }
}


void free_leaderboard_table(leaderboard_t* l){
    free_table(l->table);
    free_all_buttons(l->bg);
    free(l);
}


void update_leaderboard_table(char* filename, int player, int score){
    table_t* t = load_table_from_file(filename);

    for (int r = 0; r < t->rows; r++){
        if (t->cells[r][1]->value == player){
            t->cells[r][2]->value = score;

            char highscore[20] = "Highscore:";
            char score_num[3];
            sprintf(score_num, "%d", score);
            strcat(highscore, score_num);

            t->cells[r][2]->displayed_text = highscore;
            break;
        }
    }

    sort_leaderboard_table_by_score(t);
    save_table_to_file(t, filename);

    free_table(t);
}


void sort_leaderboard_table_by_score(table_t* t){
    int arr[t->rows];
    for (int r = 0; r < t->rows; r++){
        arr[r] = t->cells[r][SCORE_COL]->value;
    }

    sort_array_descending(arr, t->rows);
    for (int i = 0; i < t->rows; i++){
        fprintf(stderr, "%d ", arr[i]);
    }

    for (int r = 0; r < t->rows; r++){
        for (int i = 0; i < t->rows; i++){
            if (t->cells[r][SCORE_COL]->value == arr[i]){
                t->cells[r][POS_COL]->value = i;
                arr[i] = -1;
                break;
            }
        }
    }
}


void reset_leaderboard_table(){
    table_t* t = load_table_from_file(LEADERBOARD_FILE_DEF);
    save_table_to_file(t, LEADERBOARD_FILE);
    free_table(t);
}


void sort_array_ascending(int* a, int n){
    for (int i = 0; i < n; i++){
        for (int j = 1; j < (n-i); j++){
            if (a[j-1] > a[j]){
                int tmp = a[j];
                a[j] = a[j-1];
                a[j-1] = tmp;
            }
        }
    }
}


void sort_array_descending(int* a, int n){
    for (int i = 0; i < n; i++){
        for (int j = 1; j < (n-i); j++){
            if (a[j-1] < a[j]){
                int tmp = a[j];
                a[j] = a[j-1];
                a[j-1] = tmp;
            }
        }
    }
}
