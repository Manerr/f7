#include <ti/getcsc.h>
#include <fileioc.h>
#include <string.h>

#include "core.h"

uint16_t files_count;
uint8_t files_type[256];
uint16_t files_size[256];  
char files_name[256][9]; 

bool can_scroll_more; 

int16_t screen_scroll;


void init_main(){

	screen_scroll = 0;


	files_count = 0;

	char *var_name;
	uint8_t var_type;
	void *vat_ptr = NULL;
	uint8_t file_handler;

	while ((var_name = ti_DetectAny(&vat_ptr, NULL, &var_type))){

		if( var_type == OS_TYPE_APPVAR || var_type == OS_TYPE_PROT_PRGM || var_type == OS_TYPE_PRGM){
			//Weird files
			if( var_name[0] == 33 || var_name[0] == 35 ) continue;
			files_type[files_count] = var_type;


			if( var_type == OS_TYPE_PROT_PRGM || var_type == OS_TYPE_PRGM )file_handler = ti_OpenVar(var_name,"r",var_type);
			else file_handler = ti_Open(var_name,"r");

			files_size[files_count] = ti_GetSize(file_handler) + 2;
			ti_Close(file_handler);

			strcpy(files_name[files_count],var_name);
			files_count++;
		}

	}

}



void events(uint8_t key){

	switch(key){

		case sk_Right:
			break;
		case sk_Left:
			break;
		case sk_Up:
			if(screen_scroll == 0) return;
			screen_scroll++;
			break;
		case sk_Down:
			if (!can_scroll_more) return;
			screen_scroll--;
			break;

	}

}