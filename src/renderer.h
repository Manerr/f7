#include <string.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/lcd.h>


#ifndef RENDER_HEADER
#define RENDER_HEADER


#define LIGHT_BLACK 1
#define DARK_GREY 2
#define GREY 3
#define BRIGHT_GREY 4

void FillScreen(uint8_t color);
void render_loop();
void init_renderer();
void files_renderer();
void game_loop_render();

void draw_menus();
void end_gfx();
void dialog(uint8_t dialog_type);

void rename_renderer(char *name);

void init_rename_rendering();
void leave_rename_rendering();

void rename_renderer_cursor(char *name);


extern uint8_t loop_frame;
extern bool partial_redraw;

extern long intro_loop_ticks;
extern long game_loop_ticks;
extern int16_t screen_y;


#endif