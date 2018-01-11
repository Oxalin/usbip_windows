# usbip_windows

This project is a fork of the original work from hirofuchi available https://sourceforge.net/projects/usbip/

Since the development of the original code was stopped in 2012, it took a lot of delay compared to the code living under the Linux's driver. The code was not officially compatible with newer versions of Windows beyond Windows 7. Also, it would fail to work against any Linux kernel over 3.14, when the driver moved from staging to stable and was ported to libudev in the process.

Objectives
There are mostly 3 objectives to this fork:
* Have a driver compatible with newer versions of Linux kernel beyond 3.14
* Have a driver compatible with newer versions of Windows beyond Windows 7
* Have a living source code where contributors can fix and add features as a community

Any interested person willing to contribute to the code is welcome.
* The first action will be do search, find and gather patches lying around in pull requests to the original source code and in the forum.
* Next will be to have a driver compatible with Linux kernel 3.15 and newer.
