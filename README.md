# WifiKit32TelemetryReceiver & WiFiKit8TelemetryReceiver
Receive telemetry from the sister project '8266RemoteTelemetry', to display on the built-in OLED display on the Heltec WiFi Kit 32.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.


### Prerequisites

You will need:
1. A heltec WiFi Kit 32 board  or a WiFi Kit 8 board
2. Another device sending remote telemetry such as in our [8266 Remote Telemetry project](https://github.com/iot-crazy/8266RemoteTelemetry)

You will already know:
1. How to use the Arduino IDE (or IDE of your choice)
2. How to upload sketches / code to your device

### Installing

1. Clone the repo to your local computer, or copy the .ino file for the board you're using.
2. Connect the sensors to your ESP8266 board
3. Set the WiFi network name and password in the code in the correct .ino file for the board you're using
4. Upload the code to your device

## Tested On

1. Heltec Wifi Kit 32
2. Heltec WiFi Kit 8

Please let us know if you test this on other devices so we can add to the list and acknowledge your contribution!

## Trouble Shooting

### The code does not run
1. If you're using he WiFi Kit 32 board ensure you have selected the corect board in the Arduino IDE as "Heltec WiFi Kit 32", do not select the "Lora 32".
2. if you're using the WiFi Kit 8 board, ensure you've added the board via board manager [https://heltec.org/wifi_kit_install/](https://heltec.org/wifi_kit_install/)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

