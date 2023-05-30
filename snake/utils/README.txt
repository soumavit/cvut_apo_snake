utils folder        - files with functions and structs to support the run of the Snake application

mzapo utils             - mzapo_utils.c
                        - mzapo_utils.h

                        - definition and implementation of functions and structs that controll the physical aspects of MicroZed APO
                        - MicroZed APO refresh display function
                        - MicroZed APO led controls functions
                        - MicroZed APO input handle functions



game utils              - game_utils.c
                        - game_utils.h

                        - definition and implementation of functions and structs that run and draw the game
                        - game display update, score update
                        - collisions handler
                        - game fruit struct
                        - draw snake, draw fruit



theme utils             - theme_utils.c
                        - theme_utils.h

                        - definition and implementation of functions that change the app color theme
                        - set background color
                        - set buttons colors



utils                   - utils.c
                        - utils.h

                        - definition and implementation of functions that control the display buffer
                        - draw pixel, draw char, draw text..
                        - color conversions
                        - ppm loader, ppm to 565 rgb converter



leaderboard utils       - leaderboard_utils.c
                        - leaderboard_utils.h

                        - definition and implementation of functions and structs which controll the graphic side of leaderboard
                        - leaderboard struct 
                        - leaderboard uses the table_t struct to store the table
                        - leaderboard uses buttons as a way to be diplayed
                        
