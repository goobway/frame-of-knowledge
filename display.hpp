#ifndef DISPLAY_DOT_H
#define DISPLAY_DOT_H


void initialize_matrix(void);
void deinitialize_matrix(void);
void clear_matrix(void);

void draw(unsigned char mat[][32], unsigned int color);
void animate(unsigned int sequence[], unsigned int color);



#endif