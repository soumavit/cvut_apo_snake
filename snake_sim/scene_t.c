#include "scene_t.h"


scene_manager_t* scene_man_init(int n){
    scene_manager_t* scn_m = malloc(sizeof(scene_manager_t));
    if (!scn_m){
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(MEM_ALLOC_ERROR_SCENE);
    }

    scn_m->scene = malloc(sizeof(scene_t*) * n);
    if (!scn_m->scene){
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(MEM_ALLOC_ERROR_SCENE);
    }

    scn_m->num_of_scenes = n;
    return scn_m;
}


void free_all_scenes(scene_manager_t* scn_m){
    for (int i = 0; i<scn_m->num_of_scenes; i++){
        free(scn_m->scene[i]);
    }
    free(scn_m->scene);
    free(scn_m);
}
