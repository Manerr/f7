#include <ti/getcsc.h>
#include <fileioc.h>
#include <string.h>
#include <debug.h>

#include <ti/flags.h>

#include "core.h"
#include "fileops.h"

uint16_t files_count;
uint8_t files_type[1024];
uint16_t files_size[1024];
bool files_archived[1024];


uint16_t current_file_index;
uint16_t current_file_y;
int16_t screen_scroll;


char files_name[1024][9]; 

char new_file_name[9]; 
char tmp_name[9]; 

bool can_scroll_more; 

//When the use want to add characters like 1-9 (primary function of keys)
bool temporaryPrimaryKeys = false;

uint8_t mode = LISTING;
bool copying = false;

bool switchAlphaMode;

void init_main(){

	screen_scroll = 0;
	current_file_index = 0;
	current_file_y = 0;

	detect_files();

	mode = LISTING;

	switchAlphaMode = 0;

	// *OS_FLAGS_SHIFT_KEEPALPHA = 1;

}

int16_t min(int16_t a,int16_t b){
	if(a<b) return a;
	return b;
}
int16_t max(int16_t a,int16_t b){
	if(a>b) return a;
	return b;
}

void events(uint8_t key){

	switch(key){

		case sk_Left:
			screen_scroll = 0;
			current_file_index = 0;
			break;
		case sk_Right:
			current_file_index = files_count - 1;
			screen_scroll = SCROLL_BOTTOM;
			break;
		case sk_Up:

			if( current_file_index > 0 ) current_file_index--;
			if( current_file_index < screen_scroll) screen_scroll--;

			break;
		case sk_Down:

			if( current_file_index < files_count - 1 )	current_file_index++;
			if( current_file_index - screen_scroll > 11  ) screen_scroll++;

			if (!can_scroll_more) return;
			

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

		//Des-Archive
		case sk_Store:
			handle_archive(current_file_index);
			break;

	}

}


void rename_events(uint8_t key,char *tmp_file_name){

	uint8_t length = strlen(tmp_file_name);


	switch(key){

		
		//Renaming 
		case sk_Enter:
		case sk_Yequ:


			if( length ){
				handle_rename(current_file_index,tmp_file_name);
				// We dont need to jump to the end (because of having listed files again)
				// current_file_index = files_count - 1;
				// screen_scroll = SCROLL_BOTTOM;
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

		//Switch alpha keys (between upper and lower case)		
		case sk_2nd:	
			switchAlphaMode = false;
			temporaryPrimaryKeys = true; 
			break;

		//Switch alpha keys (between upper and lower case)		
		case sk_Alpha:

			switchAlphaMode = !switchAlphaMode; 
			return;

	}	



	char added_strings[2];
	// char added_char = *added_strings;

	//Characters input
	if( length < 8 ){


		//Idk if numbers are really forbidden for a name's first character , but I decided to disable this feature
		if( length == 0 && temporaryPrimaryKeys){
			temporaryPrimaryKeys = false;
			return;
		}

		added_strings[0] = 0;
		added_strings[1] = 0;

		// added_char = 0;

		switch(key){

			case sk_Math:
				*added_strings = 65;
				break;
			case sk_Apps:
				*added_strings = 66;
				break;
			case sk_Prgm:
				*added_strings = 67;
				break;
			case sk_Recip:
				*added_strings = 68;
				break;
			case sk_Sin:
				*added_strings = 69;
				break;
			case sk_Cos:
				*added_strings = 70;
				break;
			case sk_Tan:
				*added_strings = 71;
				break;
			case sk_Power:
				*added_strings = 72;
				break;
			case sk_Square:
				*added_strings = 73;
				break;
			case sk_Comma:
				*added_strings = 74;
				break;
			case sk_LParen:
				*added_strings = 75;
				break;
			case sk_RParen:
				*added_strings = 76;
				break;
			case sk_Div:
				*added_strings = 77;
				break;
			case sk_Log:
				*added_strings = 78;
				break;
			case sk_7:
				
				if(temporaryPrimaryKeys) *added_strings = 55;
				else *added_strings = 79;
				break;
			case sk_8:
				if(temporaryPrimaryKeys) *added_strings = 56;
				else *added_strings = 80;
				break;
			case sk_9:
				if(temporaryPrimaryKeys) *added_strings = 57;
				else *added_strings = 81;
				break;
			case sk_Mul:
				*added_strings = 82;
				break;
			case sk_Ln:
				*added_strings = 83;
				break;
			case sk_4:
				if(temporaryPrimaryKeys) *added_strings = 52;
				else *added_strings = 84;
				break;
			case sk_5:
				if(temporaryPrimaryKeys) *added_strings = 53;
				else *added_strings = 85;
				break;
			case sk_6:
				if(temporaryPrimaryKeys) *added_strings = 54;
				else *added_strings = 86;
				break;
			case sk_Sub:
				*added_strings = 87;
				break;
			case sk_Store:
				*added_strings = 88;
				break;
			case sk_1:
				if(temporaryPrimaryKeys) *added_strings = 49;
				else *added_strings = 89;
				break;
			case sk_2:
				if(temporaryPrimaryKeys) *added_strings = 50;
				else *added_strings = 90;
				break;
			case sk_0:
				if(temporaryPrimaryKeys) *added_strings = 48;
				break;
				
		}

		
		if( *added_strings ){

			if( switchAlphaMode ) *added_strings += 32;
			if(temporaryPrimaryKeys) temporaryPrimaryKeys = false;

			strcat(tmp_file_name,added_strings);
			
			added_strings[0] = 0;
		
		}
			

	}


}
