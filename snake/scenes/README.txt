
scenes folder       - Snake (game) scene files
                    - scenes implementation

loading screen          - loading_screen_scene.c  
                        - loading_screen_scene.h

                        - implementation of a loading screen scene
                        - displays a logo image and animates a loading process while waiting for input



main menu               - main_menu_scene.c
                        - main_menu_scene.h 

                        - implementation of a main menu scene
                        - main menu allows the user to navigate through different options such as play, options...
                        - handles user input to switch between different scenes based on the selected button



choose player           - choose_player_scene.c
                        - choose_player_scene.h

                        - implementation of a scene where the user can choose as what player he/she wants to play



1 player mode           - game_scene.c
                        - game_scene.h

                        - implementation of the game for 1 player
                        - game loop that handles input and updates the game in every tick
                        - score counter



2 player mode           - game_2_scene.c
                        - game_2_scene.h

                        - implementation of the game for 2 players
                        - game loop that handles input and updates the game in every tick
                        - score counter for each snake



game over (1 player)    - game_over_scene.c
                        - game_over_scene.h

                        - implementation of the game over scene for 1 player mode
                        - score and highscore handling



game over (2 players)   - game_2_over_scene.c
                        - game_2_over_scene.h

                        - implementation of the game over scene for 2 players mode



leaderboard             - leaderboard_scene.c
                        - leaderboard_scene.h
    
                        - implementation of the leaderboard scene
                        - leaderboard with positions, players and highscores
                        - values stored in leaderboard.txt 



options                 - options_sceme.c
                        - options_scene.h

                        - implementation of the options scene
                        - options allows the user to change different game settings, colors and theme
                        - predefined values for each option