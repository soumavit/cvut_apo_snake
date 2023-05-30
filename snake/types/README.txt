
types folder    - struct types definitions and implementation

button_t            - button_t.c
                    - button_t.h

                    - definition and implementation of button_t
                    - button with position, size, label, colors..


button_group_t      - button_t.c
                    - button_t.h

                    - definition and implementation of button_group_t
                    - can store multiple buttons and manage which one is selected etc.



option button       - option_button.c
                    - option_button.h

                    - definition and implementation of option_button_t           
                    - button with position, size, label, colors..
                    - can store more than one label
                    - can store value for each label


opt_button_group_t  - option_button.c
                    - option_button.h

                    - definition and implementation of opt_button_group_t
                    - can store multiple option buttons and manage which one is selected, what label is selected etc.



scene_t             - scene_t.c
                    - scene_t.h

                    - definition and implementation of scene_t
                    - holds pointers to the scenes initialize, update and exit functions


scene_manager_t     - scene_t.c
                    - scene_t.h

                    - definition and implementation of scene_manager_t
                    - scene manager can store multiple scenes and select between them



snake_t             - snake_t.c
                    - snake_t.h

                    - definition and implementation of snake_t
                    - methods to update the snake, enlarge the snake, set direction


tile_t              - snake_t.c
                    - snake_t.h
                    
                    - definition and implementation of tile_t
                    - tile_t represents one snake tile or one fruit tile



table_t             - table_t.c
                    - table_t.h

                    - definition and implementation of table_t
                    - table struct that can store a table of cell_t type cells


cell_t              - table_t.c
                    - table_t.h

                    - definition and implementation of cell_t
                    - cell struct that can store a value and a label