teensy-dash [![Build Status](https://travis-ci.org/ronj/teensy-dash.svg?branch=develop)](https://travis-ci.org/ronj/teensy-dash) [![Coverage Status](https://coveralls.io/repos/ronj/teensy-dash/badge.svg)](https://coveralls.io/r/ronj/teensy-dash)
===========

Circuit / code information and documentation.
=============================================


Display
-------

The display used is ST7735 controlled 1.8" TFT. It use SPI to communicate with the uC.
The Teensy has hardware SPI which makes the communication with the display much faster than on the AVR.

*	A display tutorial including code for AVR can be found here: https://learn.adafruit.com/1-8-tft-display/
*	SPI optimization techniques can be found here: http://dorkbotpdx.org/blog/paul/display_spi_optimization;
	please note, this is for a different chipset but the same rules apply.
*	The modified Adafruit library which leverages the above techniques can be found here:
	https://github.com/PaulStoffregen/Adafruit_ST7735 and a small thread discussing this can be found here:
	https://forum.pjrc.com/threads/25045-Teensy-3-1-adafruit-1-8-18-bit-color-tft-SPI-speed
*	The base Adafruit library to draw graphics is also needed and can be found here:
	https://github.com/adafruit/Adafruit-GFX-Library


NEOPixels
---------

For shift-light and alarm indication a NEOPixel strip is used. Good documentation can be found on the
Adafruit website here: https://learn.adafruit.com/adafruit-neopixel-uberguide.

One thing to note is that the pixels need to be driven logically at supply voltage. So when using a 3.3v
uC a level shifter is needed. Comparison of level shifters can be found here: http://happyinmotion.com/?p=1247


Rotary encoder
--------------

A rotary encoder tutorial can be found here: https://learn.adafruit.com/trinket-usb-volume-knob


Custom dial faces
-----------------

In the end it may be required to make custom dial faces for the modifications done to the dash.
A very exhaustive tutorial can be found here: http://mazda626.net/topic/39309-making-custom-gauge-faces/


Inspiration
-----------

*	Digital speedometer with Arduino and 7-segment display: http://matthewcmcmillan.blogspot.nl/2014/02/arduino-digital-speedometer.html
*	MPGuino and derivatives: http://ecomodder.com/wiki/index.php/MPGuino and http://mpguino.wiseman.ee/eng


Testing
=======

Setting up the integration test environment
-------------------------------------------

1. Install Cucumber
   * # sudo gem update --system
   * # sudo gem install rspec
   * # sudo gem install gherkin
   * # sudo gem install cucumber

2. Install ruby-serialport
   * # sudo gem install serialport


Contributing
============

1. Fork it (https://github.com/ronj/teensy-dash/fork)
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create new Pull Request
