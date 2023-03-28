#ifndef DISPLAY_DOT_H
#define DISPLAY_DOT_H


void initialize_matrix(void);
void deinitialize_matrix(void);
void clear_matrix(void);

void clear_OLED(void);
void color_OLED(void);

void welcome(void);

void draw(unsigned char mat[][32], unsigned char color);
void animate(unsigned int sequence[], unsigned char color, unsigned char length);
void PROMPT(unsigned char mat[][32], unsigned int sequence[], unsigned char length, unsigned char color);



#endif