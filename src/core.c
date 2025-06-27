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
int16_t screen_scroll;


char files_name[1024][9]; 

char new_file_name[9]; 
char tmp_name[9]; 

bool can_scroll_more; 

uint8_t mode = LISTING;


void init_main(){

	screen_scroll = 0;
	current_file_index = 0;
	current_file_y = 0;

	detect_files();

	mode = LISTING;

}


void events(uint8_t key){

	switch(key){

		case sk_Left:
			screen_scroll = 0;
			current_file_index = 0;
			break;
		case sk_Right:
			current_file_index = files_count - 1;
			screen_scroll = current_file_index * 4;
			break;
		case sk_Up:

			if( current_file_index > 0 ) current_file_index--;
			if(screen_scroll == 0) return;

			screen_scroll--;

			if( current_file_y < 35 ){

				if(screen_scroll > 8) screen_scroll -=  9;
				else screen_scroll = 0;
			}



			break;
		case sk_Down:
			if( current_file_y > 160 ) screen_scroll += 12;
			if( current_file_index < files_count - 1 )	current_file_index++;

			if (!can_scroll_more) return;
			screen_scroll++;
			

			break;

		//Rename 
		case sk_Window:
			mode = RENAMING;
			break;

		//Delete
		case sk_Del:
		case sk_Trace:

			handle_delete(current_file_index);
			
			break;
		//Execute - Open
		case sk_Enter:
		case sk_Yequ:
			handle_launch(current_file_index);
			break;

	}

}


void rename_events(uint8_t key,char *tmp_file_name){

	switch(key){

		//Renaming 
		case sk_Enter:
		case sk_Yequ:

			// handle_rename(current_file_index);
			mode = LISTING;
			break;

		//Leaving rename
		case sk_Clear:
		case sk_Graph:

			mode = LISTING;
			break;

		case sk_Del:


			strncpy(tmp_file_name, tmp_file_name, strlen(tmp_file_name) - 1 );

			break;

	}	 

}
