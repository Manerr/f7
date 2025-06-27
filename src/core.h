#include <string.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/lcd.h>
#include <fileioc.h>


//Modes
#define LISTING 0
#define RENAMING 1

#ifndef CORE_H
#define CORE_H


void init_main();
void events(uint8_t key);
void rename_events(uint8_t key,char *tmp_file_name);

extern uint16_t files_count;
extern uint16_t current_file_index;
extern uint16_t current_file_y;

extern uint8_t mode;

extern bool can_scroll_more;

extern uint8_t files_type[1024];  
extern float files_size[1024];  
extern char files_name[1024][9];  

extern int16_t screen_scroll;

extern char new_file_name[9]; 


#endif