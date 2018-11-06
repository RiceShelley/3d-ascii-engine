#include "screen.h"


#define S_WIDTH 220
#define S_HEIGHT 56

char *screen[S_HEIGHT];

void init_screen() {
	cx = S_WIDTH / 2;
	cy = S_HEIGHT / 2;
	fnum = S_WIDTH;

	for (int i = 0; i < S_HEIGHT; i++) {
		screen[i] = malloc(S_WIDTH);
	}	
}

void output_screen() {
	for (int j = 0; j < S_HEIGHT; j++) {
		for (int i = 0; i < S_WIDTH; i++) {
			putchar(screen[j][i]);
		}
		putchar('\n');
	}
}

void clear_screen(char c) {
	for (int j = 0; j < S_HEIGHT; j++) {
		for (int i = 0; i < S_WIDTH; i++) {
			screen[j][i] = c;
		}
	}
}

bool write_screen(int x, int y, char c) {	
	if (x > S_WIDTH - 1 || x < 0 || y > S_HEIGHT - 1 || y < 0) {
		return 0;		
	}
	screen[y][x] = c;
	return 1;
}

char get_sc_char(int x, int y) {	
	if (x > S_WIDTH - 1 || x < 0 || y > S_HEIGHT - 1 || y < 0) {
		return 0;		
	}
	return screen[y][x];
}
