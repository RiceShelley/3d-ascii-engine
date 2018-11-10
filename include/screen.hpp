#ifndef __SCREEN_H
#define __SCREEN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>
#include <iostream>

class Screen {

    private:
        // center of the screen
        double cx;
        double cy;
        double fnum;
        int s_width = 220;
        int s_height = 57;

    public:
        void init_screen();
        void output_screen();
        void clear_screen();
        bool write_screen(int x, int y, char c);
        char get_sc_char(int x, int y);
        double get_fnum();
        double get_cx();
        double get_cy();

};
#endif
