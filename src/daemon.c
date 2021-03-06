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
            case 'r': colortemp_set(6600);  break;
            case 't': {
                unsigned short temp = 0;
                if ( !sscanf(optarg, "%hu", &temp) ) {
                    fputs("colortempd: Failed to read temperature\n", stderr);
                    return EXIT_FAILURE;
                }
                if ( temp < 1000 || temp > 15000 ) {
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

    openlog(NULL, LOG_CONS, LOG_USER);
    syslog(LOG_INFO, "Started\n");

    pid_t pid = fork();
    if ( pid < 0 ) {
        syslog(LOG_ERR, "Failed to fork off\n");
        closelog();
        return EXIT_FAILURE;
    } else if ( pid > 0 ) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    pid_t sid = 0;
    if ( (sid = setsid()) < 0 ) {
        syslog(LOG_ERR, "Failed to create new process group session\n");
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO); close(STDOUT_FILENO); close(STDERR_FILENO);

    unsigned short dd_temp = 1900, noon_temp = 6600, temp_step = 100,
                   f_step = (noon_temp - dd_temp) / temp_step, m_step = 74,
                   n_step = m_step == 0 || f_step < m_step ? f_step : m_step;

    while ( 1 ) {
        unsigned dawn = 23427, dusk = 71749, noon = (dawn + dusk) / 2,
                 ttslp = (noon - dawn) / n_step;

        unsigned short t = 1000;
        colortemp_set(t);

        time_t current;
        time(&current);

        struct tm * ct = localtime(&current);
        signed curseconds = ct->tm_hour * 3600 + ct->tm_min * 60 + ct->tm_sec,
               time_to_dawn = (signed )dawn - curseconds;

        if ( time_to_dawn >= 0 ) {
            syslog(LOG_INFO, "Dawn is in %d seconds; sleeping till then\n", time_to_dawn);
            sleep((unsigned )time_to_dawn);
            t = dd_temp;
        } else {
            unsigned steps_to_skip = ((unsigned )(-time_to_dawn)) / (unsigned )ttslp;
            t = ((unsigned short )steps_to_skip * temp_step) + dd_temp;
        }

        for ( ; t <= noon_temp; t += temp_step ) {
            colortemp_set(t);
            syslog(LOG_INFO, "Set color temperature to %hu\n", t);
            sleep(ttslp);
        }

        for ( t = noon_temp; t >= dd_temp; t -= temp_step ) {
            colortemp_set(t);
            syslog(LOG_INFO, "Set color temperature to %hu\n", t);
            sleep(ttslp);
        }

        t = 1000;
        colortemp_set(t);
        syslog(LOG_INFO, "Set color temperature to 1000\n");

        time(&current);
        ct = localtime(&current);

        curseconds = ct->tm_hour * 3600 + ct->tm_min * 60 + ct->tm_sec;
        syslog(LOG_INFO, "Sleeping for %u seconds\n", (unsigned )((25 * 3600) - curseconds));
        sleep((unsigned )((25 * 3600) - curseconds));
    }

    syslog(LOG_INFO, "Shutting down\n");
    closelog();
    return EXIT_SUCCESS;
}

