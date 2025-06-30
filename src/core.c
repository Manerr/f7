#include <ti/getcsc.h>
#include <fileioc.h>
#include <string.h>
#include <debug.h>

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
bool copying = false;


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
		case sk_Zoom:
			
			handle_copy(current_file_index);
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

	uint8_t length = strlen(tmp_file_name);
	char *added_char;


	switch(key){

		//Renaming 
		case sk_Enter:
		case sk_Yequ:


			if( length ){
				handle_rename(current_file_index,tmp_file_name);
				current_file_index = files_count - 1;
				screen_scroll = current_file_index * 3;
				mode = LISTING;
				return;
			}
			else{
				break;
			}

		//Leaving rename -- if copying we just delete the tmp file used
		case sk_Clear:
		case sk_Graph:
			if( copying ){

				tmp_file_name[0] = 0;
				handle_delete(current_file_index);
				detect_files();

			}
			mode = LISTING;
			copying = false;
			return;
			// break;

		case sk_Del:

			if( length ) tmp_file_name[length - 1 ] = 0;
			return;
			// break;

	}	




	//Characters input
	if( length < 8 ){


		added_char = 0;

		switch(key){

			case sk_Math:
				added_char = "A";
				break;
			case sk_Apps:
				added_char = "B";
				break;
			case sk_Prgm:
				added_char = "C";
				break;
			case sk_Recip:
				added_char = "D";
				break;
			case sk_Sin:
				added_char = "E";
				break;
			case sk_Cos:
				added_char = "F";
				break;
			case sk_Tan:
				added_char = "G";
				break;
			case sk_Power:
				added_char = "H";
				break;
			case sk_Square:
				added_char = "I";
				break;
			case sk_Comma:
				added_char = "J";
				break;
			case sk_LParen:
				added_char = "K";
				break;
			case sk_RParen:
				added_char = "L";
				break;
			case sk_Div:
				added_char = "M";
				break;
			case sk_Log:
				added_char = "N";
				break;
			case sk_7:
				added_char = "O";
				break;
			case sk_8:
				added_char = "P";
				break;
			case sk_9:
				added_char = "Q";
				break;
			case sk_Mul:
				added_char = "R";
				break;
			case sk_Ln:
				added_char = "S";
				break;
			case sk_4:
				added_char = "T";
				break;
			case sk_5:
				added_char = "U";
				break;
			case sk_6:
				added_char = "V";
				break;
			case sk_Sub:
				added_char = "W";
				break;
			case sk_Store:
				added_char = "X";
				break;
			case sk_1:
				added_char = "Y";
				break;
			case sk_2:
				added_char = "Z";
				break;
		}

		if( added_char) strcat(tmp_file_name,added_char);
			

	}


}
