/**
 * constants.h
 * 
 * all important constant values are defined here
 * all other files can acces this file
 * 
 * created by Vit Soumar and Marek Jirku for computer architectures course semestral project
*/


#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

//errors
#define MEM_ALLOC_ERROR 101
#define FILE_ERROR 201

//scene returns EXIT_GAME when the app should close
#define EXIT_GAME -2
//scene returns SCENE_SWITCH_ERROR when something went wrong in the scene
#define SCENE_SWITCH_ERROR -1

//SCENES
enum scene_enum{LOADING_SCREEN_S, MAIN_MENU_S, OPTIONS_S, GAME_S, GAME2_S, GAME_OVER_S, GAME2_OVER_S, LEADERBOARD_S, CHOOSE_PLAYER_S};

//THEMES
enum theme_enum{CLASSIC_THEME, LIGHT_THEME, DARK_THEME};

//PLAYERS
enum player_enum{PLAYER_1, PLAYER_2, PLAYER_3, PLAYER_4, PLAYER_5, PLAYER_6};

//TEXT SIZES
enum textsize_enum{
    TEXT_1 = 1,
    TEXT_2 = 2,
    TEXT_3 = 3,
    GAME_OVER = 5,
    LOGO= 7,
};

//SCENE HEADER SIZES
enum header_enum{
    SCENE_HEADER_SIZE = 4,
    SCENE_HEADER_Y = 20,
};

//BUTTON BORDER SIZES
enum button_border_enum{
    NO_BORDER = 0,
    BORDER_1 = 1,
    BORDER_2 = 2,
};


//COLORS
enum colors{
    WHITE = 0xffff,
    BLACK = 0x0000,
    CYAN = 0x07fe,
    BLUE = 0x031f,
    YELLOW = 0xffa0,
    ORANGE = 0xfd00,
    RED = 0xf800,
    MAGENTA = 0xd01f,
    PINK = 0xf817,
    GREEN = 0x0682,
    LIME = 0xc7e0,//0x8fe0,
};


#define LEADERBOARD_FILE "/tmp/soumavit/leaderboard.txt"
#define LEADERBOARD_FILE_DEF "/tmp/soumavit/leaderboard_def.txt"
#define LOGO_FILE "/tmp/soumavit/snake.ppm"


//SCREEN SIZE
#define WIDTH 480
#define HEIGHT 320

//GAME COUNTER
#define SCORE_COUNTER_WIDTH 480
#define SCORE_COUNTER_HEIGHT 20

//SNAKE
#define SNAKE_BORDER_SIZE 1

//FONT
#define DEF_CHAR_WIDTH 14
#define DEF_CHAR_HEIGHT 16
#define DEF_TEXT_SCALE 1

//GAMES SCENE
#define DEF_SNAKE1_DIR_X 1
#define DEF_SNAKE1_DIR_Y 0

#define DEF_SNAKE1_START_X 0
#define DEF_SNAKE1_START_Y 0

#define DEF_SNAKE2_DIR_X -1
#define DEF_SNAKE2_DIR_Y 0

#define DEF_SNAKE2_START_X 480  
#define DEF_SNAKE2_START_Y 300  //320 - SCORE COUNTER HEIGHT

//TICK RATE
#define GAME_REFRESH_USEC 30000
#define REFRESH_USEC 100000


#endif /*__CONSTANTS_H__*/
