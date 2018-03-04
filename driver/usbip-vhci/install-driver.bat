rem To disable the signature checkup, uncomment the following line.
rem bcdedit /set testsigning on

rem To add the certificate, uncomment the following lines.
rem certutil -enterprise -addstore Root USBIP_TestCert.cer
rem certutil -enterprise -addstore TrustedPublisher USBIP_TestCert.cer

cd output

rem Make sure you have devcon.exe (from WinDDK / WDK) in the appropriate folder.
..\..\tools\devcon.exe install USBIPEnum.inf "root\USBIPEnum"

cd ..
