#include <string.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/lcd.h>


#include <time.h>
#include <graphx.h>

#include "renderer.h"
#include "core.h"


void FillScreen(uint8_t color);


void step(){
	return;
}

int main() {

	// prgm_CleanUp();
	os_ClrHomeFull();
	srand(time(NULL));

	FillScreen(0x00);
	init_main();
	init_renderer();


	bool app_loop = true;

	while (app_loop){


		//Intro 

		uint8_t key;
		uint8_t intro_loop = true;
		intro_loop_ticks = 0;

		while( intro_loop ){

			key = os_GetCSC();
			intro_loop_render();


			if(key) intro_loop = false;

		}

		uint8_t game_loop = true;

		if( key == sk_Clear ) {

			app_loop = false;
			game_loop = false;

		}

		//Game loop

		game_loop_ticks = 0;
		while( game_loop ){

			key = os_GetCSC();
			game_loop_render();
			

			if(key == sk_Clear) game_loop = false;

		}


	}



	gfx_End();
	os_ClrHomeFull();



	// while (os_GetCSC() != sk_Clear) {
	// 	render_loop();
	// 	events();
	// }


	return 0;
}


