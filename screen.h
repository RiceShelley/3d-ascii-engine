#ifndef __SCREEN_H
#define __SCREEN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// center of the screen
double cx;
double cy;
double fnum;

void init_screen();
void output_screen();
void clear_screen(char c);
bool write_screen(int x, int y, char c);
char get_sc_char(int x, int y);

#endif
