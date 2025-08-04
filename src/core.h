#include <string.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/lcd.h>
#include <fileioc.h>


//Modes

#ifndef CORE_H
#define CORE_H

#define LISTING 0
#define RENAMING 1
#define FAKE_COPYING 2

void init_main();
void events(uint8_t key);
void rename_events(uint8_t key,char *tmp_file_name);

extern uint16_t files_count;
extern uint16_t current_file_index;
extern uint16_t current_file_y;

extern uint8_t mode;

extern bool can_scroll_more;

extern uint8_t files_type[1024];  
extern uint16_t files_size[1024];  
extern char files_name[1024][9];  
extern bool files_archived[1024];

extern int16_t screen_scroll;

extern char new_file_name[9]; 
extern bool copying;

extern int16_t min(int16_t a,int16_t b);

extern int16_t max(int16_t a,int16_t b);

//WIP not implemented yet
//Modes to "keep in mind" what the user was doing before a garbage collector -> for example when you copy a file it's sometimes triggered...
#define GC_COPYING 1;

extern uint8_t before_gc_action;


#define SCROLL_BOTTOM max(0,files_count - 12);


#endif