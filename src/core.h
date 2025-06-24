#include <string.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/lcd.h>
#include <fileioc.h>

#ifndef CORE_H
#define CORE_H


void init_main();
void events(uint8_t key);

extern uint16_t files_count;
extern uint16_t current_file_index;
extern uint16_t current_file_y;

extern bool can_scroll_more;

extern uint8_t files_type[1024];  
extern uint16_t files_size[1024];  
extern char files_name[1024][9];  

extern int16_t screen_scroll;

#endif