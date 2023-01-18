#ifndef __PRINTK_H_
#define __PRINTK_H_


#include "console.h"

void printk(char *format, ...);

void printk_color(real_color_t back, real_color_t fore, char *format, ...);


#endif