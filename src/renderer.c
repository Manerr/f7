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


void initPalette(){

	for (uint8_t i = 0; i < 255; i++){
		// uint8_t c = 255;
		*(gfx_palette + i) = gfx_RGBTo1555(i,i,i);
	}

}

void init_renderer(){

	partial_redraw = true;
	gfx_Begin();
	gfx_SetDrawBuffer();
	initPalette();
	loop_frame = 0;
	gfx_SetTextFGColor(250);
	gfx_SetColor(20);

	intro_loop_ticks = 0;
	game_loop_ticks = 0;

	FillScreen(0x00);



}



void intro_loop_render(){

	gfx_FillScreen(0);

	char string[64];
	// gfx_PrintStringXY(string,20,200);

	uint16_t screen_y = screen_scroll * 3 - 6;


	for (char index = 0; index < files_count; index++){

		screen_y += 16;
		if( screen_y < 0 || screen_y > 238) continue;
		gfx_FillRectangle(10,screen_y - 3,300,14);
		gfx_PrintStringXY(files_name[index],20,screen_y);
		sprintf(string,"%d bytes",files_size[index]);
		gfx_PrintStringXY(string,200,screen_y);

	}


	if(screen_y > 224 ) can_scroll_more = true;
	else can_scroll_more = false;

	gfx_SwapDraw();
	intro_loop_ticks++;
}


void game_loop_render(){

	// char string[32];
	// sprintf(string,"Game frame: %ld",game_loop_ticks);

	// gfx_SetColor(0);
	// gfx_FillRectangle(0 , 0 , 144 , 16);
	// gfx_PrintStringXY(string,0,0);


	gfx_SwapDraw();
	game_loop_ticks++;
}








