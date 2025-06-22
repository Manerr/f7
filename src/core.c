#include <ti/getcsc.h>

#include "core.h"
// #include "maps.h"

struct player game_player;


void init_player(){
	game_player.x = 8;
	game_player.y = 8;
	game_player.hp = 24;

}

void init_main(){

	// init_player();
	// generate_map(1);

}

void events(){

	uint8_t key = os_GetCSC();

	switch(key){

		case sk_Right:
			game_player.x++;
			break;
		case sk_Left:
			game_player.x--;
			break;
		case sk_Up:
			game_player.y--;
			break;
		case sk_Down:
			game_player.y++;
			break;

	}

}