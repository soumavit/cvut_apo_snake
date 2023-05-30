#include "table_t.h"


cell_t* cell_init(int col, int row, char* text, int value){
    cell_t* cell = malloc(sizeof(cell_t));
    if (!cell){
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(MEM_ALLOC_ERROR_TABLE);
    }

    cell->col = col;
    cell->row = row;

    cell->displayed_text = text;
    cell->value = value;

    return cell;
}


table_t* table_init(int cols, int rows){
    table_t* table = malloc(sizeof(table_t));
    if (!table){
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(MEM_ALLOC_ERROR_TABLE);
    }

    table->cells = malloc(sizeof(cell_t*) * rows);
    if (!table->cells){
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(MEM_ALLOC_ERROR_TABLE);
    }

    for (int row = 0; row < rows; row++) {
        table->cells[row] = malloc(sizeof(cell_t) * cols);
        if (!table->cells[row]) {
            fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
            exit(MEM_ALLOC_ERROR_TABLE);
        }
    }

    table->cols = cols;
    table->rows = rows;

    return table;
}


table_t* load_table_from_file(char* filename) {
    FILE* fp;
    char line[256];
    int cols, rows;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: Could not open file '%s'\n", filename);
        exit(1);
    }

    // Read first line for table dimensions
    if (fgets(line, sizeof(line), fp) == NULL) {
        fprintf(stderr, "Error: Failed to read table dimensions from file '%s'\n", filename);
        exit(1);
    }
    sscanf(line, "%d %d", &cols, &rows);

    table_t* table = table_init(cols, rows);

    // Read remaining lines for table data
    int row = 0;
    while (fgets(line, sizeof(line), fp) != NULL && row < rows) {
        char* token;
        token = strtok(line, ";");
        int col = 0;

        while (token != NULL && col < cols) {
            char* displayed_text;
            int value;
            sscanf(token, "%ms %d", &displayed_text, &value);

            // Create cell and add to table
            table->cells[row][col] = cell_init(col, row, displayed_text, value);

            // Get next token
            token = strtok(NULL, ";");
            col++;
        }
        row++;
    }

    fclose(fp);
    return table;
}


void save_table_to_file(table_t* table, char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error: Unable to open file %s\n", filename);
        return;
    }

    fprintf(file, "%d %d\n", table->cols, table->rows);

    for (int i = 0; i < table->rows; i++) {
        for (int j = 0; j < table->cols; j++) {
            cell_t* cell = table->cells[i][j];
            fprintf(file, "%s %d; ", cell->displayed_text, cell->value);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}


void free_table(table_t* table) {
    for (int i = 0; i < table->rows; i++) {
        for (int j = 0; j < table->cols; j++) {
            cell_t* cell = table->cells[i][j];
            //free(cell->displayed_text)
            free(cell);
        }
        free(table->cells[i]);
    }
    free(table->cells);
    free(table);
}
