#ifndef _LINUX_IMPORT_H
#define _LINUX_IMPORT_H

// Since we want to talk with linux USB/IP module, we shall be able to
// to understand what we are receiving. So here, we import some of the enum and
// struct that will need to be translated from the linux module.

// Imported from Linux USB include ch9.h
enum usb_device_speed {
	USB_SPEED_UNKNOWN = 0,                  /* enumerating */
	USB_SPEED_LOW, USB_SPEED_FULL,          /* usb 1.1 */
	USB_SPEED_HIGH,                         /* usb 2.0 */
	USB_SPEED_WIRELESS,                     /* wireless (usb 2.5) */
	USB_SPEED_SUPER,                        /* usb 3.0 */
	USB_SPEED_SUPER_PLUS,                   /* usb 3.1 */
};



#endif //LINUX_IMPORT