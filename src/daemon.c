#include "daemon.h"

signed
main (signed argc, char * argv []) {

    signed temp = 6500;
    if ( argc > 1 ) { temp = atoi(argv[1]); }
    temp = (temp < 1000 || temp > 10000 ? 6500 : temp) - 1000;
    sct_set_color_temp(temp);
    return EXIT_SUCCESS;
}

