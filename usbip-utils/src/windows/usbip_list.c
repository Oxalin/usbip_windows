/*
* Copyright (C) 2018 Alexandre Demers <alexandre.f.demers@gmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <sys/types.h>
#include <sysfs/libsysfs.h>

#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <dirent.h>
#include "getopt.h"
#include <netdb.h>
#include <regex.h>
#include <unistd.h>

#include <initguid.h>
#include <setupapi.h>
#include <windows.h>
#include <winioctl.h>

#include "usbip.h"
#include "usbip_common.h"
#include "usbip_network.h"
#include "usbip_osspecific.h"
// #include "utils.h"

static const char usbip_list_usage_string[] =
    "usbip list [-p|--parsable] <args>\n"
    "    -p, --parsable         Parsable list format\n"
    "    -r, --remote=<host>    List the exported USB devices on <host>\n"
    "    -l, --local            List the local USB devices\n";

void usbip_list_usage(void)
{
    printf("usage: %s", usbip_list_usage_string);
}

// Same as static int query_exported_devices(int sockfd) under Linux
static int query_interface0(SOCKET sockfd, char * busid, struct usb_interface * uinf0)
{
	int ret;
	struct op_devlist_reply rep;
	uint16_t code = OP_REP_DEVLIST;
	uint32_t i, j;
	char product_name[100];
	char class_name[100];
	struct usb_device udev;
	struct usb_interface uinf;
	int found = 0;

	memset(&rep, 0, sizeof(rep));

	ret = usbip_send_op_common(sockfd, OP_REQ_DEVLIST, 0);
	if (ret < 0) {
		err("send op_common");
		return -1;
	}

	ret = usbip_recv_op_common(sockfd, &code);
	if (ret < 0) {
		err("recv op_common");
		return -1;
	}

	ret = usbip_recv(sockfd, (void *) &rep, sizeof(rep));
	if (ret < 0) {
		err("recv op_devlist");
		return -1;
	}

	PACK_OP_DEVLIST_REPLY(0, &rep);
	dbg("exportable %d devices", rep.ndev);

	for (i = 0; i < rep.ndev; i++) {

		memset(&udev, 0, sizeof(udev));

		ret = usbip_recv(sockfd, (void *) &udev, sizeof(udev));
		if (ret < 0) {
			err("recv usb_device[%d]", i);
			return -1;
		}
		pack_usb_device(0, &udev);
		usbip_names_get_product(product_name, sizeof(product_name),
		udev.idVendor, udev.idProduct);
		usbip_names_get_class(class_name, sizeof(class_name), udev.bDeviceClass,
		udev.bDeviceSubClass, udev.bDeviceProtocol);

		dbg("%8s: %s", udev.busid, product_name);
		dbg("%8s: %s", " ", udev.path);
		dbg("%8s: %s", " ", class_name);

		for (j = 0; j < udev.bNumInterfaces; j++) {

			ret = usbip_recv(sockfd, (void *) &uinf, sizeof(uinf));
			if (ret < 0) {
				err("recv usb_interface[%d]", j);
				return -1;
			}

			pack_usb_interface(0, &uinf);
// The following condition is not used under Linux. Where are
// we using uinf0 after this?
			if (!strcmp(udev.busid, busid) && j == 0) {
				memcpy(uinf0, &uinf, sizeof(uinf));
				found = 1;
            }
			usbip_names_get_class(class_name, sizeof(class_name),
									uinf.bInterfaceClass,
									uinf.bInterfaceSubClass,
									uinf.bInterfaceProtocol);

			dbg("%8s: %2d - %s", " ", j, class_name);
		}

		dbg(" ");
	}
// Under Linux, rep.ndev is returned instead of a 0 or -1.
	if (found)
        return 0;
	return -1;
}

int usbip_list(int argc, char *argv[])
{
  	static const struct option opts[] = {
  		{ "parsable", no_argument, NULL, 'p' },
  		{ "remote", required_argument, NULL, 'r' },
  		{ "local", no_argument, NULL, 'l' },
  		{ NULL, 0, NULL, 0 }
  	};
  	bool is_parsable = false;
  	int opt;
  	int ret = -1;

  	if (usbip_names_init(USBIDS_FILE))
        err("failed to open %s\n", USBIDS_FILE);

  	for (;;) {
        opt = getopt_long(argc, argv, "pr:l", opts, NULL);

        if (opt == -1)
            break;

        switch (opt) {
        case 'p':
            is_parsable = true;
            break;
        case 'r':
            ret = show_exported_devices(optarg);
            goto out;
        case 'l':
            if (is_parsable)
                ret = show_devices2();
            else
                ret = show_devices();
            goto out;
        default:
            goto err_out;
        }
  	}

err_out:
	usbip_list_usage();
out:
	usbip_names_free();

	return ret;
}
