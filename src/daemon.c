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
            case 'd': return colortemp_daemon();
            case 'h': fputs(usage, stdout); break;
            case 'r': colortemp_set(6500);  break;
            case 't': {
                signed temp = 0;
                if ( !sscanf(optarg, "%d", &temp) ) {
                    fputs("colortempd: Failed to read temperature\n", stderr);
                    return EXIT_FAILURE;
                }
                if ( temp < 1000 || temp > 10500 ) {
                    fputs("colortempd: Value out of range\n", stderr);
                    return EXIT_FAILURE;
                } colortemp_set(temp);
            } break;

            default: fputs(usage, stderr); return EXIT_FAILURE;
        }
    } return EXIT_SUCCESS;
}

signed
colortemp_daemon (void) {

    pid_t pid = fork();
    if ( pid < 0 ) {
        return EXIT_FAILURE;
    } else if ( pid > 0 ) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    openlog(NULL, LOG_CONS, LOG_USER);
    syslog(LOG_INFO, "Started colortempd\n");

    pid_t sid = 0;
    if ( (sid = setsid()) < 0 ) {
        syslog(LOG_ERR, "Failed to create new process group session\n");
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO); close(STDOUT_FILENO); close(STDERR_FILENO);

    for ( ; ; ) { sleep(10); }

    closelog();
    return EXIT_SUCCESS;
}
