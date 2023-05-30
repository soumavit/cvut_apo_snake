#include "snake_t.h"


snake_t* snake_init(int x, int y, int tile_size, int dir_x, int dir_y){

    snake_t* s = malloc(sizeof(snake_t));
    if (!s){
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(MEM_ALLOC_ERROR_SNAKE);
    }

    s->head = tile_init(x, y);
    s->tail = s->head;
    s->size = 1;
    s->tile_size = tile_size;

    s->dir_x = dir_x;
    s->dir_y = dir_y;
    
    return s;
}


tile_t* tile_init(int x, int y){
    tile_t* t = malloc(sizeof(tile_t));
    if (!t){
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(MEM_ALLOC_ERROR_SNAKE);
    }

    t->x = x;
    t->y = y;
    t->next = NULL;
    t->prev = NULL;

    return t;
}


void set_snake_dir(snake_t* s, int dir_x, int dir_y){
    s->dir_x = dir_x;
    s->dir_y = dir_y;
}


void update_snake(snake_t* s, bool enlarged){
    if (s->size == 1 || enlarged){
        s->head->x += s->dir_x * s->tile_size;
        s->head->y += s->dir_y * s->tile_size;
        return;
    }

    //places tail in front of head
    s->tail->x = s->head->x + s->dir_x * s->tile_size;
    s->tail->y = s->head->y + s->dir_y * s->tile_size;

    tile_t* tmp = s->tail;

    s->tail = s->tail->prev;
    s->tail->next = NULL;

    tmp->next = s->head;

    s->head->prev = tmp;
    s->head = tmp;
}


void enlarge_snake(snake_t* s){
    //after enlarging the snake, only the head of the snake should be moved
    //the new tile is placed on the same pos as the head before the head moves
    if (s->size == 1){
        tile_t* tmp = tile_init(s->head->x, s->head->y);
        tmp->prev = s->head;
        s->head->next = tmp;
        s->tail = tmp;
        s->size += 1;
        return;
    }    

    //inserts new tile between head and the tile after head
    tile_t* tmp = s->head->next;

    tile_t* new = tile_init(s->head->x, s->head->y);
    new->prev = s->head;
    new->next = tmp;

    tmp->prev = new;
    s->head->next = new;
    s->size += 1;
}


void delete_snake(snake_t* s){
    tile_t* tmp = s->head->next;

    while (tmp != NULL){
        free(tmp->prev);
        tmp = tmp->next;
    }
    free(s->tail);
    free(s);
}
