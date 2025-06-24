#include <string.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/lcd.h>
#include <ti/getkey.h>

#include <time.h>
#include <graphx.h>

#include "renderer.h"
#include "core.h"


void FillScreen(uint8_t color);


void step(){
	return;
}

int main() {

	os_ClrHomeFull();
	srand(time(NULL));

	FillScreen(0x00);
	init_main();
	init_renderer();
	gfx_ZeroScreen();

	bool app_loop = true;

	while (app_loop){

		uint8_t key;
		bool first_draw = true;
		bool list_loop = true;
		
		draw_menus();
		gfx_SwapDraw();	

		while( list_loop ){

			key = os_GetCSC();
			if(key || first_draw){
				events(key);
				files_renderer();
				first_draw = false;
			}


			if(key == sk_Clear || key == sk_Graph  ) list_loop = false;

		}

		if( key == sk_Clear || key == sk_Graph ) {
			app_loop = false;
		}




	}



	gfx_End();
	os_ClrHomeFull();

	return 0;
}


