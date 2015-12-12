#include "sct.h"

void
sct_set_color_temp (signed temp) {

    Display * dpy = XOpenDisplay(NULL);
    signed screen = DefaultScreen(dpy);
    Window root = RootWindow(dpy, screen);
    XRRScreenResources * res = XRRGetScreenResourcesCurrent(dpy, root);
    double ratio = temp % 500 / 500.0;

    signed tmp = temp / 500;
    #define AVG(c) whitepoints[tmp].c     * (1 - ratio) + \
                   whitepoints[tmp + 1].c * ratio

    for ( signed c = 0; c < res->ncrtc; ++ c ) {
        RRCrtc crtcxid = res->crtcs[c];
        signed size = XRRGetCrtcGammaSize(dpy, crtcxid);
        XRRCrtcGamma * crtc_gamma = XRRAllocGamma(size);

        for ( signed i = 0; i < size; ++ i ) {
            double g = 65535.0 * i / size;
            crtc_gamma->red[i]   = (unsigned short )(g * AVG(r));
            crtc_gamma->green[i] = (unsigned short )(g * AVG(g));
            crtc_gamma->blue[i]  = (unsigned short )(g * AVG(b));
        } XRRSetCrtcGamma(dpy, crtcxid, crtc_gamma); XFree(crtc_gamma);
    }
}

signed
main (signed argc, char * argv []) {

    signed temp = 6500;
    if ( argc > 1 ) { temp = atoi(argv[1]); }
    temp = (temp < 1000 || temp > 10000 ? 6500 : temp) - 1000;
    sct_set_color_temp(temp);
    return EXIT_SUCCESS;
}

