#include <string.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/lcd.h>

// #include <ti/sprintf.h>

#include <graphx.h>
#include <stdio.h>


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

	gfx_FillRectangle(20,220,230,20);
	gfx_SetColor(0xff);
	gfx_Rectangle(16, 220 , 48 , 17);
	gfx_PrintStringXY("Ok",31,225);


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

	//Cursor
	if(rename_cursor_tick % 20 > 10){
		gfx_SetColor(0xff);
		gfx_FillRectangle(20 + gfx_GetStringWidth(name) ,current_file_y - 2,2,12);
	}
	else{
		gfx_SetColor(LIGHT_BLACK);
		gfx_FillRectangle(20 + gfx_GetStringWidth(name) ,current_file_y - 2,2,12);
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

	gfx_FillRectangle(18,220,302,18);

	gfx_SetColor(255);

	for (int i = 0; i < 5; ++i){

		gfx_Rectangle(16 + i * 60 , 220 , 48 , 17);

	}

	gfx_PrintStringXY("Delete",199,225);

	gfx_PrintStringXY("Quit >",262,225);

	gfx_PrintStringXY("Open",24,225);
	
	gfx_PrintStringXY("Rname",80,225);


}

void dialog(uint8_t dialog_type){

}


void human_readable_size(float size,char string[]){

	if(size < 1024)	sprintf(string,"%.0f bytes",size);
	else sprintf(string,"%.1f kilobytes",size / 1000);
		// First i tried a dumb conversion to round .1 ... if someone knows ce's perfomance on this.  
	// ((uint16_t)(size / 100))/10 );

}


void files_renderer(){

	char string[32];

	gfx_ZeroScreen();
	gfx_BlitRectangle(gfx_screen,10,218,300,22);
	screen_y = - screen_scroll * 3 - 6;

	for (char index = 0; index < files_count; index++){

		screen_y += 16;
		if( screen_y < 0 || screen_y > 200) continue;

		human_readable_size(files_size[index],string);
	
		if( index == current_file_index ){

			gfx_SetTextFGColor(0x2e);
			gfx_SetColor(LIGHT_BLACK);
			gfx_FillRectangle(18,screen_y - 4 , 284,16);			
			gfx_PrintStringXY(files_name[index],20,screen_y);
			gfx_PrintStringXY(string,200,screen_y);
			gfx_SetTextFGColor(0xff);
			current_file_y = screen_y;
			gfx_SetColor(0x00);

		}
		else{
			gfx_PrintStringXY(files_name[index],20,screen_y);
			gfx_PrintStringXY(string,200,screen_y);
		}


	}


	if(screen_y > 184 ) can_scroll_more = true;
	else can_scroll_more = false;

		gfx_SwapDraw();


}




