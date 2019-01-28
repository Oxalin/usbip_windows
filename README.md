# usbip_windows

This project is a fork of the original work from hirofuchi available https://sourceforge.net/projects/usbip/

Since the development of the original code was stopped in 2012, it took a lot of delay compared to the code living under the Linux's driver. The code was not officially compatible with newer versions of Windows beyond Windows 7. Also, it would fail to work against any Linux kernel over 3.14, when the driver moved from staging to stable and was ported to libudev in the process.

Objectives
There are mostly 3 objectives to this fork:
* Have a driver compatible with newer versions of Linux kernel beyond 3.14
* Have a driver compatible with newer versions of Windows beyond Windows 7
* Have a living source code where contributors can fix and add features as a community

Any interested person willing to contribute to the code is welcome.
* The first action will be to search, find and gather patches lying around in pull requests to the original source code and in the forum.
* Next will be to have a driver compatible with Linux kernel 3.15 and newer.

# Latest updates
## January, 28th, 2019
The project's development will not continue here. After discussing with KyungWoon Cho aka Cezuni, we will be working together from his directory. The goals, bugs and feature requests will be brought into this new joint venture. Any fixes missing from this new source code that were already incorporated under my repository will be ported to this new project.

The development that was taking place in bringing the userspace tools and library from Linux to Windows (and other OSes) will also take a new life under KyungWoon's project.

Please, visit this project and report any bug or feature request here: https://github.com/cezuni/usbip-win

Persons willing to help are welcome to join the project.

## January, 8th, 2019
My computer has been set back up to be able to continue porting the userspace tools. And by this, I means the current code available from Linux.

The big problem I was facing the last time I worked on the project is the fact that these tools were ported to udev. Udev is great under Linux, but it is a major restriction for using them on other OSes. So one option would be to get the old common way of doing things from before they were ported to udev. This is not really an option because I hope to see the tools live outside of Linux's source code and this will only be accepted (hopefully) if they continue to use udev. Thus, this means that I need to use an abstraction approach to get the same results from any OS, but with different implementations. I think I have figured out how I will proceed, but I need to continue my exploration a bit more. Remember, this project also serves me to learn and develop new skills.

This approach should be used to port the tools to BSDs. I still have to figure out how hard it would be to port the drivers from Linux to BSD (I came along a FreeBSD request not so long ago).

Someone also pointed out that there is another active project aiming at having a full USP/IP implementation, with both client and server side drivers and tools. I had a quick look and it seems the userspace tools are based on the old code. While this is great to have working tools, I think we should find a way to combine both projects so the common tools could as close as possible to the ones under Linux, but with the extra Windows applications.

## December, 4th, 2018
This project is still alive even though it has been awhile since my last commit. Porting the latest Linux userspace tools was going great when I halted the development a few months ago. The problem is that I'm working on the project only in my sparetimes and, since last year, I'm newly a father which gives me a lot less of free time. The only time available is once everyone is asleep where, very often, I also just fall asleep myself.

I should resume this work shortly, which is good news: I should have time during Christmas vacation and afterward. I'm also working on other projects, like VCE for AMD's GCN 1.0, some packages here and there, some tools that I work with at work regularly (XLS to GTFS | GTFSBuilder and TransitFeed). So, I'll still have to share my time across the board.
