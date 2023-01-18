#include "printk.h"

void printk(char *format, ...) {
    console_write(format);
}

void printk_color(real_color_t back, real_color_t fore, char *format, ...) {
    console_write_color(format, back, fore);
}