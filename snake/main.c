/**
 * main file for the snake application
 * 
 * loads in the loading scene, then changes scenes accordingly and finally exits the app
 * 
 * created by Vit Soumar for computer architectures course
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "constants.h"
#include "global_values.h"

#include "scenes/loading_screen_scene.h"
#include "scenes/main_menu_scene.h"
#include "scenes/choose_player_scene.h"
#include "scenes/game_scene.h"
#include "scenes/game_over_scene.h"
#include "scenes/game_2_scene.h"
#include "scenes/game_2_over_scene.h"
#include "scenes/leaderboard_scene.h"
#include "scenes/options_scene.h"

#include "types/scene_t.h"
#include "types/button_t.h"
#include "types/option_button_t.h"
#include "types/table_t.h"

#include "utils/utils.h"
#include "utils/leaderboard_utils.h"
#include "utils/theme_utils.h"
#include "utils/mzapo_utils.h"

#include "micro_zed_files/mzapo_parlcd.h"
#include "micro_zed_files/mzapo_phys.h"
#include "micro_zed_files/mzapo_regs.h"


#define SCENE_SWITCH_ERROR_CODE 460


int main(int argc, char const *argv[]){
    MEM_BASE = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
    PARLCD_MEM_BASE = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);

    bool switch_scene = false;
    int new_scene = 0;

    //create scenes for the app
    scene_manager_t* scene_manager = scene_man_init(9);

    scene_t* load_screen_scene = create_load_screen();
    scene_t* main_menu_scene = create_main_menu();
    scene_t* options_scene = create_options();
    scene_t* game_scene = create_game();
    scene_t* game_2_scene = create_game_2();
    scene_t* game_over_scene = create_game_over();
    scene_t* game_2_over_scene = create_game_2_over();
    scene_t* leaderboard_scene = create_leaderboard();
    scene_t* choose_player_scene = create_choose_player();

    scene_manager->scene[LOADING_SCREEN_S] = load_screen_scene;
    scene_manager->scene[MAIN_MENU_S] = main_menu_scene;
    scene_manager->scene[OPTIONS_S] = options_scene;
    scene_manager->scene[GAME_S] = game_scene;
    scene_manager->scene[GAME2_S] = game_2_scene;
    scene_manager->scene[GAME_OVER_S] = game_over_scene;
    scene_manager->scene[GAME2_OVER_S] = game_2_over_scene;
    scene_manager->scene[LEADERBOARD_S] = leaderboard_scene;
    scene_manager->scene[CHOOSE_PLAYER_S] = choose_player_scene;

    scene_t* current_scene = scene_manager->scene[LOADING_SCREEN_S];
    current_scene->init(current_scene);

    refresh_display(current_scene->buffer);

    //switch scenes until the user exits the app
    while (true){

        if (switch_scene){
            switch_scene = false;
            current_scene->exit(current_scene);

            current_scene = scene_manager->scene[new_scene];
            current_scene->init(current_scene);
        }

        new_scene = current_scene->update(current_scene);

        //SCENE SWITCH ERROR is retuned when something went wrong in selecting the following scene
        if (new_scene == SCENE_SWITCH_ERROR){
            fprintf(stderr, "ERROR WHILE LOADING NEW SCENE\n");
            exit(SCENE_SWITCH_ERROR_CODE);
        }

        //exit the app
        if (new_scene == EXIT_GAME){
            unsigned int ** buffer = init_scene_buffer(WIDTH, HEIGHT);
            set_background(buffer, WIDTH, HEIGHT, BLACK);
            refresh_display(buffer);
            free_scene_buffer(buffer, HEIGHT);

            //turn off leds
            set_leds(0,0,0);
            break;
        }
        switch_scene = true;
    }
    
    current_scene->exit(current_scene);
    free_all_scenes(scene_manager);

    return 0; 
}
