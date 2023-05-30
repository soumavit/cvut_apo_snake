Snake

This game was created by Vit Soumar as a semestral project for a computer architectures course at CTU FEE


main.c              - main file
                    - create all scenes, set loading screen as current scene
                    - then switch scenes according to the user input


global_values.h     - definition of global values
                    - all files can acces this file
                    - contains variables such as current player, current score, current theme
                    - contains both current game setting and default game settings


constants.h         - definitions of all constants and enums
                    - all files can acces this file


fonts               - simple bitmap font files

micro_zed_files     - low-level access, physical address mapping, and register definitions for interacting with MicroZed APO

resources           - various game files, including a background image and leaderboard files related to a specific Snake game

scenes              - app scenes implementations

types               - struct types definitions and implementation

utils               - files with functions and structs to support the run of the application