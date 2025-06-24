#include <ti/getcsc.h>
#include <fileioc.h>
#include <string.h>

#include "core.h"
#include "fileops.h"

uint16_t files_count;
uint8_t files_type[1024];
float files_size[1024];

uint16_t current_file_index;
uint16_t current_file_y;


char files_name[1024][9]; 

bool can_scroll_more; 

uint16_t screen_scroll;


void init_main(){

	screen_scroll = 0;
	current_file_index = 0;
	current_file_y = 0;

	detect_files();

}



void events(uint8_t key){

	switch(key){

		case sk_Right:
			break;
		case sk_Left:
			break;
		case sk_Up:

			if( current_file_index > 0 ) current_file_index--;
			if(screen_scroll == 0) return;

			screen_scroll--;

			if( current_file_y < 25 ){
				if(screen_scroll > 5) screen_scroll -=  6;
				else screen_scroll =0;
			}



			break;
		case sk_Down:
			if( current_file_y > 165 ) screen_scroll += 6;
			if( current_file_index < files_count - 1 )	current_file_index++;

			if (!can_scroll_more) return;
			screen_scroll++;
			

			break;


		//Delete
		case sk_Trace:
			handle_delete(current_file_index);
			break;

	}

}


