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

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "getopt.h"
// #include <unistd.h>

#include <initguid.h>
#include <setupapi.h>
#include <windows.h>
#include <winioctl.h>

#include "vhci_driver.h"
#include "usbip.h"
#include "usbip_common.h"
#include "usbip_network.h"
#include "usbip_osspecific.h"

static const char usbip_detach_usage_string[] =
	"usbip detach <args>\n"
	"    -p, --port=<port>    " USBIP_VHCI_DRV_NAME
	" port the device is on\n";

void usbip_detach_usage(void)
{
	 printf("usage: %s", usbip_detach_usage_string);
}

int detach_port(char *port)
{
	signed char addr=atoi(port);
	HANDLE fd;
	int ret;

	fd = usbip_vbus_open();
	if (INVALID_HANDLE_VALUE == fd) {
		err("open vbus driver");
		return -1;
	}

	ret = usbip_vbus_detach_device(fd, addr);
	CloseHandle(fd);

	return ret;
}

int usbip_detach(int argc, char *argv[])
{
    static const struct option opts[] = {
        { "port", required_argument, NULL, 'p' },
        { NULL, 0, NULL, 0 }
    };
    int opt;
    int ret = -1;

    for (;;) {
        opt = getopt_long(argc, argv, "p:", opts, NULL);

        if (opt == -1)
            break;

        switch (opt) {
        case 'p':
            ret = detach_port(optarg);
            goto out;
        default:
            goto err_out;
        }
    }

    err_out:
        usbip_detach_usage();
    out:
        return ret;
}
