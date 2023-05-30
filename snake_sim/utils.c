#include "utils.h"

font_descriptor_t *fdes;


void draw_pixel(unsigned int **buffer, int x, int y, unsigned int color){
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT){
        buffer[y][x] = color;
    }
}


void draw_pixel_scaled(unsigned int **buffer, int x, int y, unsigned int color, int scale){
    for (int r = 0; r<scale; r++){
        for (int s = 0; s<scale; s++){
            buffer[y+r][x+s] = color;
        }
    }
}


int char_width(int ch) {
    int width;
        fdes = &font_winFreeSystem14x16;

    if (!fdes->width) {
        width = fdes->maxwidth;
    } else {
        width = fdes->width[ch-fdes->firstchar];
    }
    return width;
}


int string_width(char* s){
    int len = strlen(s);
    int w = 0;
    for (int i = 0; i < len; i++){
        w += char_width(s[i]);
    }
    return w;
}


void draw_char(unsigned int **buffer, int x, int y, char c, unsigned int color, int scale){
    if (scale == 0){
        return;
    }

    int w = char_width(c);
    const font_bits_t *ptr;
    fdes = &font_winFreeSystem14x16;

    if ((c >= fdes->firstchar) && (c-fdes->firstchar < fdes->size)){
        if (fdes->offset){
            ptr = &fdes->bits[fdes->offset[c-fdes->firstchar]];
        } else {
            int bw = (fdes->maxwidth+15)/16;
            ptr = &fdes->bits[(c-fdes->firstchar)*bw*fdes->height];
        }
        int i, j;
        for (i=0; i<fdes->height; i++) {
            font_bits_t val = *ptr;
            for (j=0; j<w; j++) {
                if ((val&0x8000)!=0) {
                    draw_pixel_scaled(buffer, x+scale*j, y+scale*i, color, scale);
                }
                val<<=1;
            }
            ptr++;
        }
    }
}


void draw_string(unsigned int **buffer, int x, int y, char* s, unsigned int color, int scale){
    if (scale == 0){
        return;
    }

    int len = strlen(s);
    int letter_offset = 0;

    for (int i = 0; i < len; i++){
        int w = char_width(s[i]) * scale;
        draw_char(buffer, x + letter_offset, y, s[i], color, scale);
        letter_offset += w;
    }
}


int center_text_x(int x, int w, char* s, int scale){
    int s_w = string_width(s) * scale;
    int offset = x + (w - s_w)/2;
    //int offset = x + 0;
    return offset;
}


int center_text_y(int y, int h, char* s, int scale){
    int s_h = DEF_CHAR_HEIGHT * scale;
    int offset = y + (h - s_h)/2;
    return offset;
}


unsigned int* load_ppm(int *width, int *height, const char* file){

    FILE *fp = fopen(file, "rb");
    if (!fp){
        fprintf(stderr, "unable to open file %s\n", file);
        exit(FILE_ERROR);
    }

    char header[3];
    if (fread(header, sizeof(char), 2, fp) != 2){
        fprintf(stderr, "invalid format of %s image (unable to load header)\n", file);
        exit(FILE_ERROR);
    }

    if (header[0] != 'P' || header[1] != '3'){
        fprintf(stderr, "invalid format of %s image (header is not \"P6\")\n", file);
        exit(FILE_ERROR);
    }

    if (fscanf(fp, "%d %d", width, height) != 2){
        fprintf(stderr, "invalid format of %s image (unable to load size)\n", file);
        exit(FILE_ERROR);
    }

    int max_color_value;
    if (fscanf(fp, "%d", &max_color_value) != 1){
        fprintf(stderr, "invalid format of %s image (unable to load max color value)\n", file);
        exit(FILE_ERROR);
    }

    if (max_color_value != 255){
        fprintf(stderr, "invalid format of %s image (wrong max color value)\n", file);
        exit(FILE_ERROR);
    }
    
   int image_size = (*width) * (*height) * 3;
   unsigned int* image = malloc(sizeof(unsigned int) * image_size);

   if (!image){
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(FILE_ERROR);
    }

    unsigned int c = fgetc(fp);
    if (c!='\n') ungetc(c, fp);


    for (int i = 0; i < image_size; i++){
        fscanf(fp, "%d\n", &image[i]);
    }

    fclose(fp);
    return image;
}


void save_ppm(unsigned int* image, int width, int height, char* file){

    FILE *fp = fopen(file, "w");
    if (!fp){
        fprintf(stderr, "cannot open file %s\n", file);
        exit(FILE_ERROR);
    }

    char header[] = {'P', '3', '\0'};
    if (!fprintf(fp, "%s\n", header)){
        fprintf(stderr, "unable to write to file (header)\n");
        exit(FILE_ERROR);
    }

    if (!fprintf(fp, "%d %d\n%d\n", width, height, 255)){
        fprintf(stderr, "unable to write to file (width, height, color)\n");
        exit(FILE_ERROR);
    }

    for (int i = 0; i < height * width * 3; i++){
        fprintf(fp, "%d\n", image[i]);
    }

    fclose(fp);
}


unsigned int** init_scene_buffer(int w, int h){
    unsigned int** b = malloc(sizeof(unsigned char*) * h);
    if (!b){
        fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
        exit(MEM_ALLOC_ERROR_UTILS);
    }

    for (int i = 0; i< h; i++){
        b[i] = malloc(sizeof(unsigned int) * w);
        if (!b[i]){
            fprintf(stderr, "MEMORY ALLOCATION ERROR\n");
            exit(MEM_ALLOC_ERROR_UTILS);
        }
    }
    return b;
}


void free_scene_buffer(unsigned int** buffer, int h){
    for (int i =0; i < h; i++){
        free(buffer[i]);
    }
    free(buffer);
}


void rgb565_to_rgb(unsigned int color, uint8_t *r, uint8_t* g, uint8_t *b){
    *r = (color >> 11) << 3;
    *g = ((color >> 5) & 0x3F) << 2;
    *b = (color & 0x1F) << 3;
}


unsigned int rgb_to_565(unsigned int r, unsigned int g, unsigned int b){
    unsigned int rgb_565 = 0;
    rgb_565 |= ((r >> 3) << 11);
    rgb_565 |= ((g >> 2) << 5);
    rgb_565 |= (b >> 3);

    return rgb_565;
}


unsigned int** ppm_to_565(unsigned int* image, int w, int h){
    unsigned int** b = init_scene_buffer(w, h);

    for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++){
            b[i][j] = rgb_to_565(image[(i*w*3) + j*3], image[(i*w*3) + j*3+1], image[(i*w*3) + j*3+2]);
        }
    }
    return b;
}
