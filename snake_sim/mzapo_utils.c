#include "mzapo_utils.h"

int kbhit(void)
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

void my_sleep(struct timespec delay){
    if (delay.tv_sec != 0){
        sleep(delay.tv_sec);
    }
    else {
        usleep(delay.tv_nsec);
    }
}


knobs_t* knobs_init(){
	knobs_t *k = malloc(sizeof(knobs_t));
	if (!k){
		exit(MEM_ALLOC_ERROR_KNOBS);
	}

	k->r = 0;
	k->g = 0;
	k->b = 0;

	k->r_pressed = false;
	k->g_pressed = false;
	k->b_pressed = false;

	return k;
}


void update_input(knobs_t* knobs){

    if (kbhit()){
        knobs->r_pressed = false;
        knobs->g_pressed = false;
        knobs->b_pressed = false;

        knobs->r = 0;
        knobs->g = 0;
        knobs->b = 0;

        char key = getch();

        if (key == 'w'){
            knobs->r_pressed = true;
            return;
        }

        if (key == 'q'){
            knobs->r = 2;
            return;
        }

        if (key == 'e'){
            knobs->r = 1;
            return;
        }

        if (key == 's'){
            knobs->g_pressed = true;
            return;
        }

        if (key == 'a'){
            knobs->g = 2;
            return;
        }

        if (key == 'd'){
            knobs->g = 1;
            return;
        }

        if (key == 'x'){
            knobs->b_pressed = true;
            return;
        }

        if (key == 'z'){
            knobs->b = 2;
            return;
        }

        if (key == 'c'){
            knobs->b = 1;
            return;
        }
    }

    knobs->r_pressed = false;
        knobs->g_pressed = false;
        knobs->b_pressed = false;

        knobs->r = 0;
        knobs->g = 0;
        knobs->b = 0;

    return;
}

int get_input_red(knobs_t* new, knobs_t* old){
    int ret = new->r;

    new->r = 0;
    //new->g = 0;
    //new->b = 0;

    if (ret == 1){
        return 1;
    }

    if (ret == 2){
        return -1;
    }
    
    return 0;
}

int get_input_green(knobs_t* new, knobs_t* old){
    int ret = new->g;

    //new->r = 0;
    new->g = 0;
    //new->b = 0;

    if (ret == 1){
        return 1;
    }

    if (ret == 2){
        return -1;
    }
    
    return 0;
}

int get_input_blue(knobs_t* new, knobs_t* old){
    int ret = new->b;

    //new->r = 0;
    //new->g = 0;
    new->b = 0;

    if (ret == 1){
        return 1;
    }

    if (ret == 2){
        return -1;
    }
    
    return 0;
}

bool get_press_red(knobs_t* knobs){
	return knobs->r_pressed;
}

bool get_press_green(knobs_t* knobs){
	return knobs->g_pressed;
}

bool get_press_blue(knobs_t* knobs){
	return knobs->b_pressed;
}

void set_led1(uint8_t r, uint8_t g, uint8_t b){
    return;
}

void set_led2(uint8_t r, uint8_t g, uint8_t b){
    return;
}

void set_leds(uint8_t r, uint8_t g, uint8_t b){
    return;
}

void set_ledline_on(int *led_strip, int idx){
    return;
}

void set_ledline_off(int *led_strip, int idx){
    return;
}

void reset_ledline(){
    return;
}

void fill_ledline(){
    return;
}

void led_effect1(){
    return;
}

void led_effect2(){
    return;
}

void led_effect_game_over(){
    return;
}


void refresh_display(unsigned int** buffer){
    //clear display
    //clrscr();
    clear();

    char top_border = '8';
    char side_border = '8';

    //top border
    for (int col = 0; col < WIDTH+2; col ++){
            printw("%c", top_border);
        }
    printw("\n");

    //char c = \u2588\n;

    
    

    for (int row = 0; row < HEIGHT; row++){
        //left border
        printw("%c", side_border);
        for (int col = 0; col < WIDTH; col ++){
            if (buffer[row][col] == WHITE){
                attron(COLOR_PAIR(WHITE));
                printw("#");
                attroff(COLOR_PAIR(WHITE));
            }
            else if (buffer[row][col] == BLACK){
                attron(COLOR_PAIR(BLACK));
                printw("#");
                attroff(COLOR_PAIR(BLACK));
            }
            else if (buffer[row][col] == CYAN){
                attron(COLOR_PAIR(CYAN));
                printw("#");
                attroff(COLOR_PAIR(CYAN));
            }
            else if (buffer[row][col] == BLUE){
                attron(COLOR_PAIR(BLUE));
                printw("#");
                attroff(COLOR_PAIR(BLUE));
            }
            else if (buffer[row][col] == YELLOW){
                attron(COLOR_PAIR(YELLOW));
                printw("#");
                attroff(COLOR_PAIR(YELLOW));
            }
            else if (buffer[row][col] == MAGENTA){
                attron(COLOR_PAIR(MAGENTA));
                printw("#");
                attroff(COLOR_PAIR(MAGENTA));
            }
            else if (buffer[row][col] == GREEN){
                attron(COLOR_PAIR(GREEN));
                printw("#");
                attroff(COLOR_PAIR(GREEN));
            }
            else if (buffer[row][col] == RED){
                attron(COLOR_PAIR(RED));
                printw("#");
                attroff(COLOR_PAIR(RED));
            }
            else if (buffer[row][col] == SNAKE1_COLOR){
                attron(COLOR_PAIR(MAGENTA));
                printw("#");
                attroff(COLOR_PAIR(MAGENTA));
            }
            else if (buffer[row][col] == SNAKE2_COLOR){
                attron(COLOR_PAIR(MAGENTA));
                printw("#");
                attroff(COLOR_PAIR(MAGENTA));
            }
            else if (buffer[row][col] == FRUIT_COLOR){
                attron(COLOR_PAIR(YELLOW));
                printw("#");
                attroff(COLOR_PAIR(YELLOW));
            }
        }
        //right border
        printw("%c\n", side_border);
    }
    //bottom border
    for (int col = 0; col < WIDTH+2; col ++){
            printw("%c", top_border);
        }
    printw("\n");
    refresh();
}

char** display_init(){

    char** display = malloc(sizeof(char*) * HEIGHT);
    if (!display){
        exit(MEM_ALLOC_ERROR_SIMUTILS);
    }

    for (int i = 0; i< HEIGHT; i++){
        display[i] = malloc(sizeof(char) * WIDTH);
        if (!display[i]){
            exit(MEM_ALLOC_ERROR_SIMUTILS);
        }

        //fill with chars
        for (int j = 0; j < WIDTH; j++){
            display[i][j] = ' ';
        }
    }
    return display;
}

void free_display(unsigned int** display){
    for (int i = 0; i < HEIGHT; i++){
        free(display[i]);
    }
    free(display);
}


/*int get_input_red(knobs_t* new, knobs_t* old){
    new->r_pressed = false;
    if (kbhit()) {
        int key = getch();

        if (key == 'd'){
            return 1;
        }

        if (key == 'a'){
            return - 1;
        }

        if (key == 's'){
            new->r_pressed = true;
        }
    }
    return 0;
}

int get_input_green(knobs_t* new, knobs_t* old){
    new->g_pressed = false;
	    if (kbhit()) {
        int key = getch();

        if (key == 'd'){
            return 1;
        }

        if (key == 'a'){
            return -1;
        }

        if (key == 's'){
            new->g_pressed = true;
        }
    }
    return 0;
}

int get_input_blue(knobs_t* new, knobs_t* old){
    new->b_pressed = false;
    if (kbhit()) {
        int key = getch();

        if (key == 'd'){
            return 1;
        }

        if (key == 'a'){
            return -1;
        }

        if (key == 's'){
            new->b_pressed = true;
        }
    }
    return 0;
}*/