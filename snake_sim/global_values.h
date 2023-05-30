/**
 * global_values.h
 * 
 * global values such as score, current player, current theme, mem base, parlcd_mem_base are defined here
 * option values such as snake colors, snake speed etc are also defined here
 * all of these variables need to be accesed and changed by more than one file thats why i made them global
 * 
 * default values for these variables are also defined here in case they need to be set back to default
 * 
 * created by Vit Soumar and Marek Jirku for computer architectures course semestral project
*/

#ifndef __GLOBAL_VALUES_H__
#define __GLOBAL_VALUES_H__

#include "constants.h"

//MEM
extern unsigned char *MEM_BASE;
extern unsigned char* PARLCD_MEM_BASE;

//DEFAULT VARIABLES (defined here instead of in constants just because i like it more)
extern const int DEF_TILE_SIZE;
extern const int DEF_SNAKE_SPEED;

extern const unsigned int DEF_SNAKE1_COLOR;
extern const unsigned int DEF_SNAKE2_COLOR;
extern const unsigned int DEF_FRUIT_COLOR;
extern const unsigned int DEF_SNAKE_BORDER_COLOR;

extern const int DEF_THEME;
extern const unsigned int DEF_PRIMARY_COLOR;
extern const unsigned int DEF_SECONDARY_COLOR;
extern const unsigned int DEF_GAME_BACKGROUND_COLOR;


//THEME VARIABLES
extern int THEME;

extern unsigned int PRIMARY_COLOR;
extern unsigned int SECONDARY_COLOR;
extern unsigned int GAME_BACKGROUND_COLOR;


//OPTIONS VARIABLES
extern int TILE_SIZE;
extern int SNAKE_SPEED;

extern unsigned int SNAKE1_COLOR;
extern unsigned int SNAKE2_COLOR;
extern unsigned int FRUIT_COLOR;
extern unsigned int SNAKE_BORDER_COLOR;

extern int SCORE;
extern int HIGH_SCORE;
extern int CURRENT_PLAYER;

extern int SCORE_PLAYER1;
extern int SCORE_PLAYER2;

#endif /*__GLOBAL_VALUES_H__*/
