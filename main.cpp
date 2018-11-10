#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include <ncurses.h>
#include <iostream>
#include <vector>

#include "include/screen.hpp"
#include "include/vector.hpp"
#include "include/wObjCreator.hpp"
#include "include/worldObj.hpp"

Screen sc;
ObjCreator woc;
// collection of objects that make up world
std::vector<WorldObj*> world;

int gameloop() {
	double pvf = 0;
	// camera
	Vector cam(0, 0, 0);

	// player object
	WorldObj player(5, 0, 10);
	woc.construct_rect(&player);
	world.push_back(&player);

	WorldObj cube(0, 0, 10);
	woc.construct_cube(&cube, 1);
	world.push_back(&cube);

	bool jump = false;

	// main game loop
	while (true) {
		// get player key input
		int key_in = getch();
		sc.output_screen();
		// player controls 
		if (key_in == 'w') {
			player.obj_move(0, 0, .2);
		} else if (key_in == 's') {
			player.obj_move(0, 0, -.2);
		} else if (key_in == 'd') {
			player.obj_move(.1, 0, 0);
		} else if (key_in == 'a') {
			player.obj_move(-.1, 0, 0);
		} else if (key_in == 'x') {
			player.obj_set_pos(0, 0, 10);
		} else if (key_in == 'j') {
			if (!jump) {
				player.obj_move(0, -.01, 0);
				pvf = -.4;
				jump = !jump;
			}
		}

		if (pvf < 1) {
			pvf += .04;
		}
		Vector v = player.get_pos();
		if (v.y < 0) {
			v.y += pvf;
			player.obj_set_pos(v.x, v.y, v.z);
		} else if (jump) {
			player.obj_set_pos(v.x, 0, v.z);
			jump = !jump;
		}

		// render world
		sc.clear_screen();
		for (WorldObj *wo : world) {
			wo->render(&sc);
		}
		sc.output_screen();
		usleep(1000);
	}
}

int main() {
	sc.init_screen();
	clear();
	gameloop();
	nocbreak();
	endwin();	
	return 0;
}
