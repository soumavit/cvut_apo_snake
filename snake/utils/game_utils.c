#include "game_utils.h"


fruit_t* fruit_init(){
    fruit_t* f = malloc(sizeof(fruit_t));
    if (!f){
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(MEM_ALLOC_ERROR);
    }
    f->x = 0;
    f->y = 0;

    return f;
}


void move_fruit_random(fruit_t* fruit, snake_t* snake, int w, int h){
    bool spawned = false;

    int new_x, new_y;
    
    time_t t;
    srand((unsigned) time(&t));

    while(!spawned){
        spawned = true;

        new_x = rand() % (w / snake->tile_size);
        new_y = rand() % (h / snake->tile_size);

        new_x *= snake->tile_size;
        new_y *= snake->tile_size;

        //go through all the snake tiles and check if the new fruit coords arent inside of the snake
        tile_t* tmp = snake->head->next;
        while (tmp != NULL){
            if (new_x == tmp->x && new_y == tmp->y){
                spawned = false;
                break;
            }
            tmp = tmp->next;
        }
    }
    fruit->x = new_x;
    fruit->y = new_y;
}


void move_fruit_random_2(fruit_t* fruit, snake_t* snake1, snake_t* snake2, int w, int h){
    bool spawned = false;

    int new_x, new_y;
    
    time_t t;
    srand((unsigned) time(&t));

    while(!spawned){
        spawned = true;

        new_x = rand() % (w / snake1->tile_size);
        new_y = rand() % (h / snake1->tile_size);

        new_x *= snake1->tile_size;
        new_y *= snake1->tile_size;

        //go through all the snake tiles and check if the new fruit coords arent inside of the snake 1
        tile_t* tmp = snake1->head->next;
        while (tmp != NULL){
            if (new_x == tmp->x && new_y == tmp->y){
                spawned = false;
                break;
            }
            tmp = tmp->next;
        }

        if (!spawned) continue;

        //go through all the snake tiles and check if the new fruit coords arent inside of the snake 2
        tmp = snake2->head->next;
        while (tmp != NULL){
            if (new_x == tmp->x && new_y == tmp->y){
                spawned = false;
                break;
            }
            tmp = tmp->next;
        }
    }
    fruit->x = new_x;
    fruit->y = new_y;
}


void update_game_display(unsigned int** buffer, snake_t* s, fruit_t* f, unsigned int background_c, int w, int h){
    //rewrite all pixels to black
    set_background(buffer, w, h, background_c);
    //draw fruit
    draw_snake_tile(buffer, f->x, f->y, FRUIT_COLOR, SNAKE_BORDER_COLOR);
    //draw snake
    draw_snake(buffer, s, SNAKE1_COLOR, SNAKE_BORDER_COLOR);
}


void update_game_display_2(unsigned int** buffer, snake_t* s1, snake_t* s2, fruit_t* f, unsigned int background_c, int w, int h){
    //rewrite all pixels to black
    set_background(buffer, w, h, background_c);
    //draw fruit
    draw_snake_tile(buffer, f->x, f->y, FRUIT_COLOR, SNAKE_BORDER_COLOR);

    //draw both snakes
    draw_snake(buffer, s1, SNAKE1_COLOR, SNAKE_BORDER_COLOR);
    draw_snake(buffer, s2, SNAKE2_COLOR, SNAKE_BORDER_COLOR);
}


bool collision(snake_t* s, int w, int h){
    if (s->head->x < 0 || s->head->y < 0 || (s->head->x + s->tile_size) > w || (s->head->y + s->tile_size) > h) return true;

    if (s->size < 5) return false;

    //the head cannot hit itself nor the tile after nor the tile after
    //thats why there is so many nexts
    tile_t* tmp = s->head->next->next->next->next;
    while (tmp != NULL){
        if (s->head->x == tmp->x && s->head->y == tmp->y) return true;
        tmp = tmp->next;
    }
    return false;
}


bool collision_2(snake_t* this, snake_t* other, int w, int h){
    if (collision(this, w, h)) return true;

    //check if this snakes head didnt collide with some of others snake tiles
    tile_t* tmp = other->head;
    while (tmp != NULL){
        if (this->head->x == tmp->x && this->head->y == tmp->y) return true;
        tmp = tmp->next;
    }
    return false;
}


void update_score(unsigned int **buffer, button_t* score_counter, int score){
    //create the score text
    char score_counter_text[100] = "Score: " ;
    char score_num[3];
    sprintf(score_num, "%d", score);
    strcat(score_counter_text, score_num);

    score_counter->label = score_counter_text;
    draw_button(buffer, score_counter);
}   


int set_game_speed(){
    switch (SNAKE_SPEED)
    {
    case 1:
        return GAME_REFRESH_USEC * 5;
    case 2:
        return GAME_REFRESH_USEC * 4;
    case 3:
        return GAME_REFRESH_USEC * 3;
    case 4:
        return GAME_REFRESH_USEC * 2;
    case 5:
        return GAME_REFRESH_USEC;
    default:
        return GAME_REFRESH_USEC * 3;
    }
}


void draw_snake(unsigned int** buffer, snake_t* s, unsigned int color, unsigned int border_color){
    
    if (s->size == 1){
        draw_snake_tile(buffer, s->head->x, s->head->y, color, border_color);
    } else {
        tile_t* tmp = s->head;
        while (tmp != NULL){
            draw_snake_tile(buffer, tmp->x, tmp->y, color, border_color);
        tmp = tmp->next;
        }
    }
}


void draw_snake_tile(unsigned int** buffer, int x, int y, unsigned int snake_c, unsigned int border_c){
    draw_pixel_scaled(buffer, x, y, snake_c, TILE_SIZE);

    //draw border
    for (int r = 0; r < SNAKE_BORDER_SIZE; r++){
        for (int s = 0; s < TILE_SIZE; s++){
            draw_pixel(buffer, x+s, y+r, border_c);
        }
    }

    for (int r = SNAKE_BORDER_SIZE; r < TILE_SIZE - SNAKE_BORDER_SIZE; r++){
        for (int s = 0; s < SNAKE_BORDER_SIZE; s++){
            draw_pixel(buffer, x+s, y+r, border_c);
        }
        for (int s = TILE_SIZE - SNAKE_BORDER_SIZE; s < TILE_SIZE; s++){
            draw_pixel(buffer, x+s, y+r, border_c);
        }

    }

    for (int r = TILE_SIZE - SNAKE_BORDER_SIZE; r < TILE_SIZE; r++){
        for (int s = 0; s < TILE_SIZE; s++){
            draw_pixel(buffer, x+s, y+r, border_c);
        }
    }
}
