#ifndef DISPLAY_DOT_H
#define DISPLAY_DOT_H


void matrix_init(void);
void matrix_deinit(void);
void clear_matrix(void);

void static_image(unsigned char mat[][32], unsigned char color);
void animated_image(unsigned int sequence[], unsigned char length, unsigned char color);
void update_matrix(int location, unsigned char color);


#endif