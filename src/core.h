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

extern bool can_scroll_more;

extern uint8_t files_type[256];  
extern uint16_t files_size[256];  
extern char files_name[256][9];  

extern int16_t screen_scroll;

#endif