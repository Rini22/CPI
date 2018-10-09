#include <stdio.h>
#include <X11/Xlib.h>

int main(void) {  
   Display *dpy = XOpenDisplay(":0"); 
   XKeyboardState x;
   XGetKeyboardControl(dpy, &x);
   XCloseDisplay(dpy);
   printf("led_mask=%lx\n", x.led_mask);
   printf("NumLock is %s\n", (x.led_mask & 2) ? "On" : "Off");
 printf("CAPSLock is %s\n", (x.led_mask & 1) ? "On" : "Off");
 printf("scrollLock is %s\n", (x.led_mask & 3) ? "On" : "Off");
   return 0;
}
