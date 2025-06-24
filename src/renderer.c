#include <string.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/lcd.h>

// #include <ti/sprintf.h>

#include <graphx.h>
#include <stdio.h>


#include "renderer.h"
#include "core.h"

bool partial_redraw;
uint8_t loop_frame = 0;
long intro_loop_ticks;
long game_loop_ticks;


void FillScreen(uint8_t color)
{
	memset(lcd_Ram, color, LCD_SIZE);
}


uint8_t min(uint8_t a,uint8_t b){

	if(a > b) return b;
	return a;

}

//Will just fill the some of the first entries to have some grayscale colors
void initPalette(){

	*(gfx_palette + 1) = gfx_RGBTo1555(40,40,40);
	*(gfx_palette + 2) = gfx_RGBTo1555(90,90,90);
	*(gfx_palette + 3) = gfx_RGBTo1555(150,150,150);
	*(gfx_palette + 4) = gfx_RGBTo1555(200,200,200);

	// for (uint8_t i = 0; i < 255; i++){
	// 	*(gfx_palette + i) = gfx_RGBTo1555(i,i,i);
	// }

}

void init_renderer(){

	partial_redraw = true;
	gfx_Begin();
	gfx_SetDrawBuffer();
	
	initPalette();

	loop_frame = 0;
	gfx_SetTransparentColor(0xf0);
	gfx_SetTextTransparentColor(0xf0);
	gfx_SetTextBGColor(0xf0);
	gfx_SetTextFGColor(255);
	gfx_SetColor(DARK_GREY);

	intro_loop_ticks = 0;
	game_loop_ticks = 0;

	current_file_y = 0;

	gfx_PrintStringXY("Loading...",180,120);	


}


void draw_menus(){



}


void human_readable_size(uint16_t size,char string[]){

	if(size < 1024)	sprintf(string,"%d bytes",size);
	else sprintf(string,"%.1f kilobytes",(float)(size) / 1000);
		// First i tried a dumb conversion to round .1 ... if someone knows ce's perfomance on this.  
	// ((uint16_t)(size / 100))/10 );

}


void files_renderer(){

	char string[32];

	gfx_ZeroScreen();
	uint16_t screen_y = screen_scroll * 3 - 6;

	for (char index = 0; index < files_count; index++){

		screen_y += 16;
		if( screen_y < 0 || screen_y > 198) continue;


		if( index == current_file_index ){

			gfx_SetTextFGColor(0x2e);
			gfx_PrintStringXY(files_name[index],20,screen_y);
			gfx_SetTextFGColor(0xff);
			current_file_y = screen_y;

		}
		else gfx_PrintStringXY(files_name[index],20,screen_y);



		human_readable_size(files_size[index],string);
		gfx_PrintStringXY(string,200,screen_y);

	}


	if(screen_y > 184 ) can_scroll_more = true;
	else can_scroll_more = false;



	gfx_SwapDraw();
	intro_loop_ticks++;
}




