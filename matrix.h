#ifndef MATRIX_DOT_H
#define MATRIX_DOT_H

void initialize_matrix(void);
void deinitialize_matrix(void);
void draw_matrix(unsigned char mat[][32]);
void clear_matrix(void);
void draw_A(void);
void animate_A(void);
void test(void);

extern unsigned char PRINT_A[32][32];
extern unsigned int ANIMATE_A[];

#endif