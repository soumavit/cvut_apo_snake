#include "game_2_scene.h"

int GAME2_WIDTH;
int GAME2_HEIGHT;


scene_t* create_game_2(){
    scene_t* scene = malloc(sizeof(scene_t));
    if (!scene){
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(MEM_ALLOC_ERROR_GAME2);
    }

    scene->init = init_game_2;
    scene->update = update_game_2;
    scene->exit = exit_game_2;
    return scene;
}


void init_game_2(scene_t* scene) {
    GAME2_HEIGHT = HEIGHT - SCORE_COUNTER_HEIGHT;
    GAME2_WIDTH = WIDTH;

    scene->buffer = init_scene_buffer(WIDTH, HEIGHT);
    set_background(scene->buffer, WIDTH, HEIGHT, GAME_BACKGROUND_COLOR);
}


int update_game_2(scene_t* scene) {
    int game_speed = set_game_speed();

    //game loop delay
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = game_speed};

    //start pause delay
    struct timespec stop_delay = {.tv_sec = 1, .tv_nsec = 0};

    my_sleep(loop_delay);

    snake_t* snake1 = snake_init(DEF_SNAKE1_START_X, DEF_SNAKE1_START_Y, TILE_SIZE, DEF_SNAKE1_DIR_X, DEF_SNAKE1_DIR_Y);
    enlarge_snake(snake1);

    snake_t* snake2 = snake_init(DEF_SNAKE2_START_X - TILE_SIZE, DEF_SNAKE2_START_Y-TILE_SIZE, TILE_SIZE, DEF_SNAKE2_DIR_X, DEF_SNAKE2_DIR_Y);
    enlarge_snake(snake2);

    fruit_t* fruit = fruit_init();
    move_fruit_random_2(fruit, snake1, snake2, GAME2_WIDTH, GAME2_HEIGHT);

    //create score counter for snake 1
    button_t* score_s1_b = button_init(0, GAME2_HEIGHT, SCORE_COUNTER_WIDTH/2, SCORE_COUNTER_HEIGHT, "Score:___", TEXT_1, BORDER_1);
    if (THEME == CLASSIC_THEME){
        score_s1_b->border_color = BLACK;
        score_s1_b->color = BLACK;
        score_s1_b->label_color = SNAKE1_COLOR;
    } else{
        score_s1_b->border_color = SECONDARY_COLOR;
        score_s1_b->color = SECONDARY_COLOR;
        score_s1_b->label_color = SNAKE1_COLOR;
    }

    //create score counter for snake 2
    button_t* score_s2_b = button_init(GAME2_WIDTH/2, GAME2_HEIGHT, SCORE_COUNTER_WIDTH/2, SCORE_COUNTER_HEIGHT, "Score:___", TEXT_1, BORDER_1);
    if (THEME == CLASSIC_THEME){
        score_s2_b->border_color = BLACK;
        score_s2_b->color = BLACK;
        score_s2_b->label_color = SNAKE2_COLOR;
    } else{
        score_s2_b->border_color = SECONDARY_COLOR;
        score_s2_b->color = SECONDARY_COLOR;
        score_s2_b->label_color = SNAKE2_COLOR;
    }

    //set score to 0 at the start
    update_score(scene->buffer, score_s1_b, snake1->size-2);
    update_score(scene->buffer, score_s2_b, snake2->size-2);
    
    update_game_display_2(scene->buffer, snake1, snake2, fruit, GAME_BACKGROUND_COLOR, GAME2_WIDTH, GAME2_HEIGHT);
    refresh_display(scene->buffer);

    knobs_t* knobs_new = knobs_init();
    knobs_t* knobs_old = knobs_init();

    update_input(knobs_new);
    update_input(knobs_old);
    
    //snake1 snake2 and fruit colors
    uint8_t s1_r, s1_g, s1_b;
    uint8_t s2_r, s2_g, s2_b;
    uint8_t f_r, f_g, f_b;
    rgb565_to_rgb(SNAKE1_COLOR, &s1_r, &s1_g, &s1_b);
    rgb565_to_rgb(SNAKE2_COLOR, &s2_r, &s2_g, &s2_b);
    rgb565_to_rgb(FRUIT_COLOR, &f_r, &f_g, &f_b);

    reset_ledline();
    //set leds colors to match the snake colors
    set_led1(s1_r, s1_g, s1_b);
    set_led2(s2_r, s2_g, s2_b);

    my_sleep(stop_delay);

    bool game_end = false;
    bool fruit_eaten_s1 = false;
    bool fruit_eaten_s2 = false;

    while(1){
        my_sleep(loop_delay);

        //stop the effect from eating an apple
        if (fruit_eaten_s1 || fruit_eaten_s2){
            set_led1(s1_r, s1_g, s1_b);
            set_led2(s2_r, s2_g, s2_b);
            reset_ledline();
        }
        if (game_end == true){
            break;
        }

        update_input(knobs_new);

        //controls snake1
        int red_knob = get_input_red(knobs_new, knobs_old);
        //controls snake2
        int blue_knob = get_input_blue(knobs_new, knobs_old);

        //snake 1
        if (red_knob > 0){
            update_input(knobs_old);
            set_snake_dir(snake1, -1 * snake1->dir_y, snake1->dir_x);
        }
        if (red_knob < 0){
            update_input(knobs_old);
            set_snake_dir(snake1, snake1->dir_y, -1 * snake1->dir_x);
        }

        //snake 2
        if (blue_knob > 0){
            update_input(knobs_old);
            set_snake_dir(snake2, -1 * snake2->dir_y, snake2->dir_x);
        }
        if (blue_knob < 0){
            update_input(knobs_old);
            set_snake_dir(snake2, snake2->dir_y, -1 * snake2->dir_x);
        }

        //check both snakes if they hadnt eaten an apple
        fruit_eaten_s1 = (fruit->x == snake1->head->x && fruit->y == snake1->head->y);
        fruit_eaten_s2 = (fruit->x == snake2->head->x && fruit->y == snake2->head->y);

        if (fruit_eaten_s1){
            enlarge_snake(snake1);
            update_score(scene->buffer, score_s1_b, snake1->size-2);

            set_leds(f_r, f_g, f_b);
            
            move_fruit_random_2(fruit, snake1, snake2, GAME2_WIDTH, GAME2_HEIGHT);
        }
        if (fruit_eaten_s2){
            enlarge_snake(snake2);
            update_score(scene->buffer, score_s2_b, snake2->size-2);

            set_leds(f_r, f_g, f_b);
            
            move_fruit_random_2(fruit, snake1, snake2, GAME2_WIDTH, GAME2_HEIGHT);
        }

        //update the snakes
        update_snake(snake1, fruit_eaten_s1);
        update_snake(snake2, fruit_eaten_s2);

        //check if one of the snakes collided
        if (collision_2(snake1, snake2, GAME2_WIDTH, GAME2_HEIGHT)){
            //player 1 COLLIDED

            //set leds to red
            set_leds(255, 0, 0);

            led_effect_game_over();
            fill_ledline();
            break;
        }
        if (collision_2(snake2, snake1, GAME2_WIDTH, GAME2_HEIGHT)){
            //player 2 COLLIDED

            //set leds to red 
            set_leds(255, 0, 0);
            led_effect_game_over();


            fill_ledline();
            break;
        }

        //update game display (if none of the snakes didnt collide)
        update_game_display_2(scene->buffer, snake1, snake2, fruit, GAME_BACKGROUND_COLOR, GAME2_WIDTH, GAME2_HEIGHT);
        refresh_display(scene->buffer);
    }

    SCORE_PLAYER1 = snake1->size - 2; //-2 because the snake starts with 2 tiles
    SCORE_PLAYER2 = snake2->size - 2;

    //free all alocated memory
    free(knobs_new);
    free(knobs_old);
    free(fruit);
    delete_snake(snake1);
    delete_snake(snake2);
    free(score_s1_b);
    free(score_s2_b);

    return GAME2_OVER_S;
}


void exit_game_2(scene_t* scene){
    for (int i =0; i < HEIGHT; i++){
        free(scene->buffer[i]);
    }
    free(scene->buffer);
}
