#include "include/screen.hpp"

void Screen::init_screen() {
	initscr();
	noecho();
	curs_set(FALSE);
	timeout(30);
	cbreak();
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