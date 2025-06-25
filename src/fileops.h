#include <string.h>
#include <ti/screen.h>
#include <ti/getcsc.h>
#include <sys/lcd.h>
#include <fileioc.h>

#include "core.h"


#ifndef FILEOPS_H
#define FILEOPS_H


void handle_delete(uint16_t tmp_index);
void handle_launch(uint16_t tmp_index);
void detect_files();


#endif