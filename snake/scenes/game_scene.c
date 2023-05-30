#include "game_scene.h"

int GAME_WIDTH;
int GAME_HEIGHT;


scene_t* create_game(){
    scene_t* scene = malloc(sizeof(scene_t));
    if (!scene){
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(MEM_ALLOC_ERROR);
    }

    scene->init = init_game;
    scene->update = update_game;
    scene->exit = exit_game;

    return scene;
}


void init_game(scene_t* scene) {
    GAME_HEIGHT = HEIGHT - SCORE_COUNTER_HEIGHT;
    GAME_WIDTH = WIDTH;

    scene->buffer = init_scene_buffer(WIDTH, HEIGHT);
    set_background(scene->buffer, WIDTH, HEIGHT, GAME_BACKGROUND_COLOR);
}


int update_game(scene_t* scene) {
    int game_speed = set_game_speed();

    //game loop delay
    struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = game_speed};

    //start pause delay
    struct timespec stop_delay = {.tv_sec = 1, .tv_nsec = 0};

    my_sleep(loop_delay);

    //create snake of size 1 and then make it 2 tiles (enlarge function)
    snake_t* snake = snake_init(DEF_SNAKE1_START_X, DEF_SNAKE1_START_Y, TILE_SIZE, DEF_SNAKE1_DIR_X, DEF_SNAKE1_DIR_Y);
    enlarge_snake(snake);

    //create fruit and place it randomly
    fruit_t* fruit = fruit_init();
    move_fruit_random(fruit, snake, GAME_WIDTH, GAME_HEIGHT);

    //update game state
    update_game_display(scene->buffer, snake, fruit, GAME_BACKGROUND_COLOR, GAME_WIDTH, GAME_HEIGHT);

    //initialize score counter and set its colors and label
    button_t* score_counter_b = button_init(0, GAME_HEIGHT, SCORE_COUNTER_WIDTH, SCORE_COUNTER_HEIGHT, "Score:___", TEXT_1, BORDER_1);
    
    score_counter_b->border_color = SECONDARY_COLOR;
    score_counter_b->color = SECONDARY_COLOR;
    score_counter_b->label_color = PRIMARY_COLOR;

    //set score counter to 0
    update_score(scene->buffer, score_counter_b, snake->size-2);
    refresh_display(scene->buffer); 

    //initialize knobs for input
    knobs_t* knobs_new = knobs_init();
    knobs_t* knobs_old = knobs_init();

    //load current state of knobs into the structs
    update_input(knobs_new);
    update_input(knobs_old);
    
    //set ledline clear in case it already isnt
    reset_ledline();
    
    //snake and fruit color
    uint8_t s_r, s_g, s_b;
    uint8_t f_r, f_g, f_b;
    rgb565_to_rgb(SNAKE1_COLOR, &s_r, &s_g, &s_b);
    rgb565_to_rgb(FRUIT_COLOR, &f_r, &f_g, &f_b);

    //set led color to snake color
    set_leds(s_r, s_g, s_b);
    my_sleep(stop_delay);

    bool game_end = false;
    bool fruit_eaten = false;

    while (1){
        my_sleep(loop_delay);

        if (fruit_eaten){
            set_leds(s_r, s_g, s_b);
            reset_ledline();
        }

        if (game_end == true){
            break;
        }

        update_input(knobs_new);

        int blue_knob = get_input_blue(knobs_new, knobs_old);

        if (blue_knob > 0){
            update_input(knobs_old);
            set_snake_dir(snake, -1 * snake->dir_y, snake->dir_x);
        }
        if (blue_knob < 0){
            update_input(knobs_old);
            set_snake_dir(snake, snake->dir_y, -1 * snake->dir_x);
        }

        fruit_eaten = (fruit->x == snake->head->x && fruit->y == snake->head->y);

        if (fruit_eaten){
            enlarge_snake(snake);
            update_score(scene->buffer, score_counter_b, snake->size-2);

            set_leds(f_r, f_g, f_b);

            move_fruit_random(fruit, snake, GAME_WIDTH, GAME_HEIGHT);
        }

        update_snake(snake, fruit_eaten);

        if (collision(snake, GAME_WIDTH, GAME_HEIGHT)){
            //set leds to red color
            set_leds(255, 0, 0);
            led_effect_game_over();

            fill_ledline();
            break;
        }

        update_game_display(scene->buffer, snake, fruit, GAME_BACKGROUND_COLOR, GAME_WIDTH, GAME_HEIGHT);
        refresh_display(scene->buffer);
    }

    SCORE = snake->size - 2; //-2 because snake starts with 2 tiles

    //free all alocated memory
    free(knobs_new);
    free(knobs_old);
    free(fruit);
    delete_snake(snake);
    free(score_counter_b);

    return GAME_OVER_S;
}


void exit_game(scene_t* scene){
    free_scene_buffer(scene->buffer, HEIGHT);
}
