#ifndef __CONSOLE_H_
#define __CONSOLE_H_

#include "types.h"
#include "port.h"

typedef
enum real_color {
    rc_black            = 0,
    rc_blue             = 1,
    rc_green            = 2,
    rc_cyan             = 3,
    rc_red              = 4,
    rc_magenta          = 5,
    rc_brown            = 6,
    rc_light_grey       = 7,
    rc_dark_grey        = 8,
    rc_light_blue       = 9,
    rc_light_green      = 10,
    rc_light_cyan       = 11,
    rc_light_red        = 12,
    rc_light_magenta    = 13,
    rc_light_brown      = 14,
    rc_white            = 15
} real_color_t;

void console_clear();

void console_putc_color(char c, real_color_t back, real_color_t fore);

void console_write(char *cstr);

void console_write_color(char *cstr, real_color_t back, real_color_t fore);

#endif