#include <ti/getcsc.h>
#include <fileioc.h>
#include <string.h>

#include "core.h"

uint16_t files_count;
uint8_t files_type[256];
long files_weight[256];  
char files_name[256][9];  

long screen_scroll;


void init_main(){

	screen_scroll = 0;


	files_count = 0;

	char *var_name;
	uint8_t var_type;
	void *vat_ptr = NULL;

	while ((var_name = ti_DetectAny(&vat_ptr, NULL, &var_type))){

		if( var_type == OS_TYPE_APPVAR ){
			files_type[files_count] = var_type;
			strcpy(files_name[files_count],var_name);
			files_count++;
		}

	}

}



void events(){

	uint8_t key = os_GetCSC();

	switch(key){

		case sk_Right:
			break;
		case sk_Left:
			break;
		case sk_Up:
			if(screen_scroll == 0) return;
			screen_scroll--;
			break;
		case sk_Down:
			screen_scroll++;
			break;

	}

}