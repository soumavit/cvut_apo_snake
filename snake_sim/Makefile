all: comp run

comp:
	gcc -o main main.c scene_t.c main_menu_scene.c loading_screen_scene.c choose_player_scene.c theme_utils.c game_scene.c game_over_scene.c game_2_scene.c game_2_over_scene.c game_utils.c options_scene.c leaderboard_scene.c leaderboard_utils.c table_t.c mzapo_utils.c snake_t.c utils.c font_rom8x16.c font_prop14x16.c global_values.c button_t.c option_button_t.c -lncurses -g -Wall

run:
	./main

all_s:
	gcc -o main2 main2.c snake.c -lncurses && ./main2