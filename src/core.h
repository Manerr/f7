#include <string.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/lcd.h>

#ifndef CORE_H
#define CORE_H

struct player
{
	uint8_t x;
	uint8_t y;
	uint8_t hp;
};

extern struct player game_player;

void init_main();

void events();

#endif