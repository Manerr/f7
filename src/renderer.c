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
		uint8_t c = 255;
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
	FillScreen(1);

	intro_loop_ticks = 0;
	game_loop_ticks = 0;



}



void intro_loop_render(){

	char string[32];
	// sprintf(string,"Intro frame: %ld",intro_loop_ticks);

	// gfx_SetColor(0);
	// gfx_FillRectangle(0 , 0 , 144 , 16);
	// gfx_PrintStringXY(string,0,0);

	char y = -screen_scroll;

	uint8_t screen_y;

	for (char index = 0; index < files_count; ++index){

		screen_y = y * 16;

		if( screen_y < 0 ) continue;
		else if( screen_y > 240 ) return;
		gfx_PrintStringXY(files_name[index],0,screen_y);
		y++;
		// strcpy(files_name[files_count],var_name);



	}




	gfx_SwapDraw();
	intro_loop_ticks++;
}


void game_loop_render(){

	char string[32];
	// sprintf(string,"Game frame: %ld",game_loop_ticks);

	// gfx_SetColor(0);
	// gfx_FillRectangle(0 , 0 , 144 , 16);
	// gfx_PrintStringXY(string,0,0);


	gfx_SwapDraw();
	game_loop_ticks++;
}








