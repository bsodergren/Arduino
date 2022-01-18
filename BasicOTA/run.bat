@ECHO OFF
SET PATH=%PATH%;d:\Arduino\bin
arduino-cli compile -e -b esp8266:esp8266:nodemcuv2 d:\Arduino\BasicOTA
arduino-cli upload -p COM7 -b esp8266:esp8266:nodemcuv2 d:\Arduino\BasicOTA
