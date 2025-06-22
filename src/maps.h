#include <string.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/lcd.h>


#ifndef MAP_H
#define MAP_H 


struct map_struct {

	uint8_t data[30][40];
	uint8_t level;

};

extern struct map_struct map;


void generate_map(uint8_t level);

#endif