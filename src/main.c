#include <string.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/lcd.h>
#include <ti/getkey.h>

#include <time.h>
#include <graphx.h>

#include "renderer.h"
#include "core.h"
#include "main.h"

void FillScreen(uint8_t color);


void before_gc(){
	gfx_End();
	os_ClrHomeFull();
}

void after_gc(){
	callback_main(NULL,0);
}


int callback_main(void *data, int retval){

	srand(time(NULL));
	os_ClrHomeFull();

	//Prevents the possible gc prompt from being not visible; for now it "destroys" app's state
	ti_SetGCBehavior(before_gc,NULL);

	

	FillScreen(0x00);
	init_main();
	init_renderer();
	gfx_ZeroScreen();

	bool app_loop = true;




	//Data sent back by the callback;
	if(data != NULL){
		uint16_t *tmp_data = ((uint16_t*)data);
		current_file_index = tmp_data[0];
		current_file_y = tmp_data[1];
		screen_scroll = tmp_data[2];
	}




	while (app_loop){



		uint8_t key;
		bool first_draw = true;
		bool list_loop = true;
		
		draw_menus();
		gfx_SwapDraw();	


		//Listing files
		while( list_loop ){

			key = os_GetCSC();
			if(key || first_draw){
				events(key);
				files_renderer();
				first_draw = false;
			}


			if(mode == RENAMING || mode == FAKE_COPYING || key == sk_Clear || key == sk_Graph ) list_loop = false;

		}

		if( key == sk_Clear || key == sk_Graph ) {
			app_loop = false;
		}



		if( mode == RENAMING || mode == FAKE_COPYING ){
			if(mode == FAKE_COPYING) copying = true;
			files_renderer();
			draw_menus();
			init_rename_rendering();
			mode = RENAMING;
		}

		first_draw = true;

		//Renaming file
		while( mode == RENAMING ){

			key = os_GetCSC();
			if(key || first_draw){
				rename_events(key,new_file_name);
				rename_renderer(new_file_name);
				first_draw = false;
			}
			rename_renderer_cursor(new_file_name);

		}

		leave_rename_rendering();




	}

	gfx_End();
	os_ClrHomeFull();

	return 0;

}




int main() {

	//Same subroutine used in main and subprograms' returns.
	callback_main(NULL,0);

	return 0;
}


