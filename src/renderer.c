#include <string.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/lcd.h>

// #include <ti/sprintf.h>

#include <graphx.h>
#include <stdio.h>


#include "renderer.h"
#include "core.h"
// #include "maps.h"

bool partial_redraw;
uint8_t loop_frame = 0;
long intro_loop_ticks;
long game_loop_ticks;


void FillScreen(uint8_t color)
{
	memset(lcd_Ram, color, LCD_SIZE);
}


void randColor(){
 
	gfx_SetColor(rand() % 256);

}

uint8_t min(uint8_t a,uint8_t b){

	if(a > b) return b;
	return a;

}

void randRect(){

	//Instead of calling rand multiple times we just store its value - kicked out
	// long r = rand();

	gfx_FillRectangle(rand() % 320,rand() % 240,1,1);

}

void initPalette(){

	for (uint8_t i = 0; i < 255; i++){
		uint8_t c = 255;
		*(gfx_palette + i) = gfx_RGBTo1555(i,i,i);
	}

	// *(gfx_palette + 40) = gfx_RGBTo1555(255,255,255);

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
	sprintf(string,"Intro frame: %ld",intro_loop_ticks);

	gfx_SetColor(0);
	gfx_FillRectangle(0 , 0 , 144 , 16);
	gfx_PrintStringXY(string,0,0);


	gfx_SwapDraw();
	intro_loop_ticks++;
}


void game_loop_render(){

	char string[32];
	sprintf(string,"Game frame: %ld",game_loop_ticks);

	gfx_SetColor(0);
	gfx_FillRectangle(0 , 0 , 144 , 16);
	gfx_PrintStringXY(string,0,0);


	gfx_SwapDraw();
	game_loop_ticks++;
}









//Dont look at this bruh it's a part of a code i tried to make
void render_loop(){


	// if (partial_redraw) gfx_BlitScreen();
	// gfx_SwapDraw(); // Queue the buffered frame to be displayed

	// gfx_FillScreen(0);

	uint8_t current_cell;
	uint8_t diff_x;
	uint8_t diff_y;
	uint8_t dist;

	uint8_t drawnrectangles = 0;

	for (int y = 0; y < 30; ++y){
		for (int x = 0; x < 40; ++x){


			diff_x = abs(game_player.x - x);
			diff_y = abs(game_player.y - y);
			dist = min(diff_x,diff_y);

			current_cell = map.data[y][x];

			if( diff_x < 10 && diff_y < 10 && current_cell < 246 ){
				
				switch (dist){

					case 0:
						map.data[y][x] += 10;
						break;
					case 1:
						map.data[y][x] += 9;
						break;
					case 2:
						map.data[y][x] += 8;
						break;
					case 3:
						map.data[y][x] += 7;
						break;
					case 4:
						map.data[y][x] += 6;
						break;
					case 5:
						map.data[y][x] += 5;
						break;
				}

			}


			if(current_cell > 4 ){
				gfx_SetColor(current_cell);
				map.data[y][x] -= 4;
				if(current_cell < 6 ) map.data[y][x] = 0;	
				gfx_FillRectangle(x * 8 , y * 8 , 8 , 8);
				drawnrectangles++;
			}


		}
	}


	// logic();
	// gfx_FillScreen(current_cell);

	char string[32];
	sprintf(string,"fps: %d | rect_drawn :__%d__  ",loop_frame,drawnrectangles);

	gfx_SetColor(0);
	gfx_FillRectangle(10 , 200 , 200 , 16);
	gfx_PrintStringXY(string,10,200);

	loop_frame++;
	gfx_SwapDraw(); // Queue the buffered frame to be displayed

}