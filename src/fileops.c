#include <ti/getcsc.h>
#include <fileioc.h>
#include <string.h>
#include <graphx.h>
#include <debug.h>

#include <ti/vars.h>
#include <ti/getkey.h>

#include "core.h"
#include "main.h"
#include "fileops.h"
#include "renderer.h"

void detect_files(){

	files_count = 0;

	char *var_name;
	uint8_t var_type;
	void *vat_ptr = NULL;
	uint8_t file_handler;

	while ((var_name = ti_DetectAny(&vat_ptr, NULL, &var_type))){

		if( var_type == OS_TYPE_APPVAR || var_type == OS_TYPE_PROT_PRGM || var_type == OS_TYPE_PRGM){
			//Weird files
			if( var_name[0] == 33 || var_name[0] == 35 || strcmp(var_name,"F7") == 0 ) continue;
			files_type[files_count] = var_type;

			if( var_type == OS_TYPE_PROT_PRGM || var_type == OS_TYPE_PRGM )file_handler = ti_OpenVar(var_name,"r",var_type);
			else file_handler = ti_Open(var_name,"r");

			files_size[files_count] = (float)ti_GetSize(file_handler) + 2.0;
			ti_Close(file_handler);

			strcpy(files_name[files_count],var_name);
			files_count++;

		}


	}

}

void handle_rename(uint16_t tmp_index,char *new_name){

	ti_RenameVar(files_name[tmp_index],new_name,files_type[tmp_index]);
	detect_files();

}

void handle_copy(uint16_t tmp_index){


    uint8_t source, destination;
    char buffer[128]; 
    size_t bytesRead;

    uint8_t file_type = files_type[tmp_index];
    
    source = ti_OpenVar(files_name[tmp_index], "r",file_type);

    if (!source) {
        return;
    }

    //Temp file used for copying - the user will in fact just rename it after lol 
    destination = ti_OpenVar("F7CPYTMP", "w",file_type);
    if (!destination) {

        ti_Close(source);
        ti_Close(destination);
        return;
    }

    while ((bytesRead = ti_Read(buffer, 1, sizeof(buffer), source)) > 0) {
        
        ti_Write(buffer, 1,bytesRead, destination);


    }

    ti_Close(source);
    ti_Close(destination);

		
	detect_files();

	current_file_index = files_count - 1;
	screen_scroll = current_file_index * 3;
	mode = FAKE_COPYING;



}




void handle_delete(uint16_t tmp_index){


	ti_DeleteVar(files_name[tmp_index],files_type[tmp_index]);

	detect_files();
	current_file_index--;
	screen_scroll -= 6;

	if(current_file_index < 0) current_file_index = 0;
	if(screen_scroll < 0) screen_scroll = 0;

}

void handle_launch(uint16_t tmp_index){

	if(files_type[tmp_index] == OS_TYPE_APPVAR ) return;

	end_gfx();

	uint16_t data[] = {current_file_index,current_file_y,screen_scroll};

	//Idk if putting the main routine as callback is very good (I hope it's not doing a recursive thing lol)
	os_RunPrgm(files_name[tmp_index],data,sizeof data,callback_main);



}