/**
 * table_t.h
 * 
 * This file can be used to:
 * - load a table from file
 * - Store table and save table to file
 * - Both in predefined style
 * 
 * created by Vit Soumar and Marek Jirku for computer architectures course semestral project
*/


#ifndef __TABLE_T_H__
#define __TABLE_T_H__


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#define MEM_ALLOC_ERROR_TABLE 304
#define FILE_ERROR_TABLE 501


/**
 * struct holding the information about one table cell
*/
typedef struct cell_t{
    int row;
    int col;
    char* displayed_text;
    int value;
} cell_t;

/**
 * struct holding the table information
*/
typedef struct table_t{
    int rows;
    int cols;
    cell_t*** cells;

} table_t;

/**
 * create and return pointer to a cell_t struct
*/
cell_t* cell_init(int col, int row, char* text, int value);

/**
 * create table_t struct with rows rows and cols colums and returns a pointer to it
*/
table_t* table_init(int cols, int rows);

/**
 * loads table from a file with predefined format
*/
table_t* load_table_from_file(char* filename);

/**
 * saves table to a file in the same predefined file as it was loaded from
*/
void save_table_to_file(table_t* table, char* filename);

/**
 * free all memory allocated for the table struct
*/
void free_table(table_t* table);

#endif /*__TABLE_T_H__*/
