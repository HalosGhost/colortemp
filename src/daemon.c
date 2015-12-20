#include "daemon.h"

signed
main (signed argc, char * argv []) {

    if ( argc <= 1 ) {
        fputs(usage, stderr);
        return EXIT_FAILURE;
    }

    for ( signed oi = 0, c = getopt_long(argc, argv, vos, os, &oi);
          c != -1;       c = getopt_long(argc, argv, vos, os, &oi)  ) {

        switch ( c ) {
            case 'h': fputs(usage, stdout); break;
            case 't': {
                signed temp = 0;
                sscanf(optarg, "%d", &temp);
                temp = temp < 1000 || temp > 10500 ? 6500 : temp;
                colortemp_set(temp - 1000);
            }

            default: fputs(usage, stderr); return EXIT_FAILURE;
        }
    } return EXIT_SUCCESS;
}
