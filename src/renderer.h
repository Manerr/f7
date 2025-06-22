#include <string.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/lcd.h>


#ifndef RENDER_HEADER
#define RENDER_HEADER


void FillScreen(uint8_t color);
void render_loop();
void init_renderer();
void intro_loop_render();
void game_loop_render();


extern uint8_t loop_frame;
extern bool partial_redraw;

extern long intro_loop_ticks;
extern long game_loop_ticks;


#endif