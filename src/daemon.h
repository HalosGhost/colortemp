#pragma once

#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include "colortemp.h"

static const char vos [] = "ht:";

static struct option os [] = {
    { "help",     0, 0, 'h' },
    { "set-temp", 1, 0, 't' },
    { 0,          0, 0, 0   }
};

static const char usage [] =
    "Usage: colortempd [options]\n"
    "colortempd -- a simple daemon for handling screen temperature in X\n\n"
    "Options:\n"
    "  -h, --help            List this help and exit\n"
    "  -t, --set-temp=NUM    Set the screen's color temperature to NUM\n";
