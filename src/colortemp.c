#include "colortemp.h"

void
colortemp_set (signed temperature) {

    signed temp = temperature - 1000;
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
