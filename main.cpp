#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include <ncurses.h>
#include <iostream>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <cstdlib>

#include "include/screen.hpp"
#include "include/vector.hpp"
#include "include/wObjCreator.hpp"
#include "include/worldObj.hpp"

Screen sc;
ObjCreator woc;
// collection of objects that make up world
std::vector<WorldObj*> world;
//path to music
const char *musi_filename = "music.wav";
// music
Mix_Music *music = NULL;
bool run = true;

void start_screen() {
	attron(COLOR_PAIR(3));
	WorldObj cube(5, 0, 15);
	woc.construct_cube(&cube, 1);
	world.push_back(&cube);

	while (true) {
		cube.rx += .01;
		cube.ry += .008;
		cube.rz += .01;
		sc.clear_screen();
		cube.render(&sc);
		int x, y;
		getmaxyx(stdscr, y, x);
		y /= 3;
		x /= 4;
		move(y, x);
		printw(" __   __     ______     __  __     ______      ______     ______     __   __    ");
		move(y + 1, x);
		printw("/\\ \"-.\\ \\   /\\  ___\\   /\\_\\_\\_\\   /\\__  _\\    /\\  ___\\   /\\  ___\\   /\\ \"-.\\ \\   ");
		move(y + 2, x);
		printw("\\ \\ \\-.  \\  \\ \\  __\\   \\/_/\\_\\/_  \\/_/\\ \\/    \\ \\ \\__ \\  \\ \\  __\\   \\ \\ \\-.  \\  ");
		move(y + 3, x);
		printw(" \\ \\_\\\\\"\\_\\  \\ \\_____\\   /\\_\\/\\_\\    \\ \\_\\     \\ \\_____\\  \\ \\_____\\  \\ \\_\\\\\"\\_\\ ");
		move(y + 4, x);
		printw("  \\/_/ \\/_/   \\/_____/   \\/_/\\/_/     \\/_/      \\/_____/   \\/_____/   \\/_/ \\/_/ ");

		x += 10;
		y += 6;
		move(y + 1, x + 10);
		printw("With love, by Rice Shelley");
		move(y + 3, x + 20);
		printw("Eat your heart our vulkan");
		move(y + 10, x + 15);
		printw("Press p to play, e to exit");
		sc.output_screen();
		int k = getch();
		if (k == 'p') {
			world.pop_back();
			return;
		} else if (k == 'e') {
			run = false;
			return;
		}
		usleep(10000);
	}
	attron(COLOR_PAIR(1));
}

void init_sdl() {
	SDL_Init(SDL_INIT_EVERYTHING);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	music = Mix_LoadMUS(musi_filename);
	Mix_PlayMusic(music, -1);
}

void gameloop() {
	// camera
	Vector cam(0, 0, 0);
	Vector crot(0, 0, 0);
	double player_pos = 0;
	double score = 0;

	// construct world
	WorldObj floor(6, 1, 21);
	woc.construct_box(&floor, 11, .1, 20);

	WorldObj ceiling(6, -2, 41);
	woc.construct_box(&ceiling, 11, .1, 1);
	ceiling.rx = 3.14 / 2;

	WorldObj wall_l(-5, 0, 21);
	woc.construct_box(&wall_l, .1, 1, 20);

	WorldObj wall_r(17, 0, 21);
	woc.construct_box(&wall_r, .1, 1, 20);

	double speed = .3;

	// main game loop
	while (true) {

		if (rand() % 100 < 10) {
			int pos = rand() % 20;
			WorldObj *obj = new WorldObj(pos - 3, 0, 30);
			woc.construct_cube(obj, .5);
			world.push_back(obj);
		}

		// get player key input
		int key_in = getch();

		if (cam.x > 5 || cam.x < -5) {
			cam.x = 0;
		}

		// player controls 
		if (key_in == 'd' && cam.x > -.5) {
			cam.x += -.3;
		} else if (key_in == 'a' && cam.x < .5) {
			cam.x += .3;
		} else {
			if (cam.x > .1) {
				cam.x -= .08;
			} else if (cam.x < -.1) {
				cam.x += .08;
			} else {
				cam.x = 0;
			}
		}

		if (player_pos < -10) {
			cam.x = 9.9;
		} else if (player_pos > 10) {
			cam.x = -9.9;
		}

		crot.y = .01;
		crot.x = .01;
		crot.z = .01;

		sc.clear_screen();

		move(0, 0);
		player_pos = floor.get_pos().x;
		printw("%f", player_pos);

		// render world
		Vector v = ceiling.get_pos();	
		point p;
		v.convert_2d(&p);
		move((int) p.y, (int) p.x);
		printw("Score: %d", (int) score);

		v = floor.get_pos();
		v.x += cam.x;
		floor.obj_set_pos(v);
		floor.render(&sc);

		v = wall_l.get_pos();
		v.x += cam.x;
		wall_l.obj_set_pos(v);
		wall_l.render(&sc);

		v = wall_r.get_pos();
		v.x += cam.x;
		wall_r.obj_set_pos(v);
		wall_r.render(&sc);

		v = ceiling.get_pos();
		v.x += cam.x;
		ceiling.obj_set_pos(v);
		ceiling.render(&sc);


		// render cubes
		for (int i = 0; i < world.size(); i++) {
			int color = (i % 6) + 2;
			attron(COLOR_PAIR(color));

			WorldObj *obj = world.at(i);
			v = obj->get_pos();
			if (v.z > 1) {
				v.x += cam.x;
				v.y += cam.y;
				v.z -= speed;
				obj->rx += crot.x;
				obj->ry += crot.y;
				obj->rz += crot.z;
				obj->obj_set_pos(v);
			}
			if (v.z > 1 && v.z < 40) {
				obj->render(&sc);
			}				
			if (v.z < 1) {
				// see if player is touching cube
				if (obj->get_pos().x < 1 && obj->get_pos().x > -1) {
					// clear world array
					for (int j = 0; j < world.size(); j++) {
						obj = world.at(i);
						delete obj;
						world.erase(world.begin() + i);
					}
					// draw game over screen
					sc.clear_screen();
					move((int) sc.get_cy(), (int) sc.get_cx());
					printw("GAME OVER.\n");
					move((int) sc.get_cy() + 1, (int) sc.get_cx());
					printw("final score: %d", score);
					move((int) sc.get_cy() + 2, (int) sc.get_cx());
					printw("press any key to continue");
					sc.output_screen();
					usleep(100000);
					timeout(-1);
					getch();
					timeout(30);
					return;
				}
				delete obj;
				world.erase(world.begin() + i);
			}
		}

		sc.output_screen();
		score += .5;
		usleep(1000);
	}
}

int main() {
	init_sdl();
	sc.init_screen();
	clear();
	start_screen();
	while (run) {
		gameloop();
		start_screen();
	}
	nocbreak();
	endwin();	
	return 0;
}
