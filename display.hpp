#ifndef DISPLAY_DOT_H
#define DISPLAY_DOT_H


void initialize_matrix(void);
void deinitialize_matrix(void);
void clear_matrix(void);

void clear_OLED(void);
void SC_PROMPT(void);

void welcome(void);

void draw(unsigned char mat[][32], unsigned char color);
void animate(unsigned int sequence[], unsigned char color, unsigned char length);
void update_matrix(int location, unsigned char color);
void PROMPT(unsigned char mat[][32], unsigned int sequence[], unsigned char length, unsigned char color, unsigned int pic);



#endif