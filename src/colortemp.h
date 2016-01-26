#pragma once


#include <X11/extensions/Xrandr.h>
#include <X11/extensions/Xrender.h>
#include <stdint.h>
#include <math.h>

struct RGB {
    double r, g, b;
};

double
getRfromTemp (unsigned short ncolor);

double
getGfromTemp (unsigned short ncolor);

double
getBfromTemp (unsigned short ncolor);

// valid range: [1000..15000]
// effective range: [1000,1100..15000]
struct RGB
getRGBfromTemp (unsigned short color);

void colortemp_set (unsigned short);
