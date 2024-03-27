# Time Tracking Big Red Button

A big red button that, when pressed, documents the current time and date and displays it on a local network website.

Done:
- Hello world
- Button pressed
- Date and time
- Web server

Need to do:
- Screen output
- Final script

Different files:
- final script
	- When button pressed
		- Add current data and time to html page
		- Show ip address to screen. Turn off screen after 2 seconds.
			- Shows that there still is battery and as a confirmation that the button was pressed.

- 1st get working with wired power
- 2nd get working with usb power bank
	- Need 555 timer keep awake circuit

## Uploading to [ESP 32](https://www.amazon.com/gp/product/B0718T232Z/ref=ppx_yo_dt_b_asin_title_o00_s01?ie=UTF8&psc=1)
1. Download Arduino IDE
2. File -> Preferences -> Additional boards manager URLs: `https://dl.espressif.com/dl/package_esp32_index.json`
3. Boards Manager -> esp32 Install
4. In terminal
```
sudo adduser <username> dialout
sudo chmod a+rw /dev/ttyUSB0
```
5. Select `NodeMCU-32S` board
