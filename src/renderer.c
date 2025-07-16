#include <string.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/lcd.h>

// #include <ti/sprintf.h>

#include <graphx.h>
#include <stdio.h>
#include <debug.h>


#include "renderer.h"
#include "core.h"

uint8_t rename_cursor_tick;

bool partial_redraw;

int16_t screen_y;


void FillScreen(uint8_t color)
{
	memset(lcd_Ram, color, LCD_SIZE);
}


//Will just fill the some of the first entries to have some grayscale colors
void initPalette(){

	*(gfx_palette + 1) = gfx_RGBTo1555(30,30,30);
	*(gfx_palette + 2) = gfx_RGBTo1555(90,90,90);
	*(gfx_palette + 3) = gfx_RGBTo1555(150,150,150);
	*(gfx_palette + 4) = gfx_RGBTo1555(200,200,200);

}

void init_rename_rendering(){

	gfx_SetColor(0);

	gfx_FillRectangle_NoClip(20,220,230,20);
	gfx_SetColor(0xff);
	gfx_Rectangle_NoClip(16, 220 , 48 , 17);
	gfx_PrintStringXY("Ok",32,225);


	gfx_SetTextFGColor(0xe8);
	gfx_SetColor(0);

	rename_cursor_tick = 0;

	


}

void leave_rename_rendering(){

	gfx_SetTransparentColor(0xf8);
	gfx_SetTextTransparentColor(0xf8);
	gfx_SetTextBGColor(0xf8);
	gfx_SetTextFGColor(255);
	gfx_SetColor(0xFF);

	draw_menus();
	gfx_SwapDraw();	


}


void rename_renderer(char *name){


	gfx_SetColor(LIGHT_BLACK);
	gfx_FillRectangle(20,current_file_y - 2,80,14);
	gfx_SetColor(0xff);
	
	gfx_PrintStringXY(name,20,current_file_y);
	gfx_BlitBuffer();


}

void rename_renderer_cursor(char *name){

	if(rename_cursor_tick % 20 > 10){
		gfx_SetColor(0xff);
		gfx_FillRectangle_NoClip(20 + gfx_GetStringWidth(name) ,current_file_y - 2,2,12);
	}
	else{
		gfx_SetColor(LIGHT_BLACK);
		gfx_FillRectangle_NoClip(20 + gfx_GetStringWidth(name) ,current_file_y - 2,2,12);
	}

	rename_cursor_tick++;
	gfx_BlitBuffer();

}




void init_renderer(){

	partial_redraw = true;
	gfx_Begin();
	gfx_SetDrawBuffer();
	
	initPalette();

	gfx_SetTransparentColor(0xf8);
	gfx_SetTextTransparentColor(0xf8);
	gfx_SetTextBGColor(0xf8);
	gfx_SetTextFGColor(255);
	gfx_SetColor(0xFF);

	current_file_y = 0;

	gfx_PrintStringXY("Loading...",180,120);	


}

void end_gfx(){
	gfx_End();
	os_ClrHomeFull();
}


void draw_menus(){

	gfx_SetColor(0);

	gfx_FillRectangle_NoClip(18,220,302,18);

	gfx_SetColor(255);

	for (int i = 0; i < 5; ++i){

		gfx_Rectangle_NoClip(16 + i * 60 , 220 , 48 , 17);

	}

	gfx_PrintStringXY("Delete",199,225);

	gfx_PrintStringXY("Quit >",262,225);

	gfx_PrintStringXY("Open",24,225);
	
	gfx_PrintStringXY("Rname",81,225);

	gfx_PrintStringXY("Copy",144,225);


}

void dialog(uint8_t dialog_type){

}


void human_readable_size(uint16_t size, char *string) {
    int i = 0;
    if (size < 1000) {
        int s = (int)size;
        if (s >= 100) string[i++] = '0' + (s/100);
        if (s >= 10)  string[i++] = '0' + ((s/10)%10);
        string[i++] = '0' + (s%10);
        memcpy(string + i, " bytes", 6); i += 6;
        string[i] = 0;
    } else {
        int kb10 = (int)((size * 10) / 1000);
        int kb = kb10 / 10;
        int dec = kb10 % 10;
        if (kb >= 100) string[i++] = '0' + (kb/100);
        if (kb >= 10)  string[i++] = '0' + ((kb/10)%10);
        string[i++] = '0' + (kb % 10);
        string[i++] = '.';
        string[i++] = '0' + dec;
        memcpy(string + i, " kbytes", 7); i += 7;
        string[i] = 0;
    }
}


void files_renderer(){

	char string[16];

	gfx_ZeroScreen();
	gfx_BlitRectangle(gfx_screen,10,218,300,22);

	screen_y = 5;
	dbg_printf("--------------start draw--------------\n");

	uint16_t index_max = files_count - 1;

	index_max = min(screen_scroll + 12,files_count);

	for (uint16_t index = screen_scroll; index < index_max; index++){

		dbg_printf("drawn index: %d\n", index);

		screen_y += 16;
		human_readable_size(files_size[index],string);
	
		if( index == current_file_index ){

			gfx_SetTextFGColor(0x2e);
			gfx_SetColor(LIGHT_BLACK);
			gfx_FillRectangle_NoClip(18,screen_y - 4 , 284,16);			
			gfx_PrintStringXY(files_name[index],20,screen_y);
			gfx_PrintStringXY(string,223,screen_y);
			gfx_SetTextFGColor(0xff);
			current_file_y = screen_y;
			gfx_SetColor(0x00);

		}
		else{
			gfx_PrintStringXY(files_name[index],20,screen_y);
			gfx_PrintStringXY(string,223,screen_y);
		}


	}



	gfx_SwapDraw();
	
	dbg_printf("--------------end draw--------------\n");


}




