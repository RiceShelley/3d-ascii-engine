#include "include/screen.hpp"

void Screen::init_screen() {
	initscr();
	noecho();
	curs_set(FALSE);
	timeout(30);
	cbreak();
	// lets make some colors
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_MAGENTA);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_BLUE, COLOR_BLACK);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
	wbkgd(stdscr, COLOR_PAIR(2));
	attron(COLOR_PAIR(1));
	refresh();
	getmaxyx(stdscr, s_height, s_width);
	cx = s_width / 2;
	cy = s_height / 2;
	fnum = s_width;
}

void Screen::output_screen() {
	refresh();
}

void Screen::clear_screen() {
	clear();
}

bool Screen::write_screen(int x, int y, char c) {	
	if (x > s_width - 1 || x < 0 || y > s_height - 1 || y < 0) {
		return 0;		
	}
	mvaddch(y, x, c);
	return 1;
}

char Screen::get_sc_char(int x, int y) {	
	return mvinch(y, x);
}

double Screen::get_fnum() {
	return fnum;
}

double Screen::get_cx() {
	return cx;
}

double Screen::get_cy() {
	return cy;
}