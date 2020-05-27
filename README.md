# WifiKit32TelemetryReceiver
Receive telemetry from the sister project '8266RemoteTelemetry', to display on the built-in OLED display on the Heltec WiFi Kit 32.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.


### Prerequisites

You will need:
1. A heltec Wifi Kt 32 board 
2. Another device sending remote telemetry such as in our [8266 Remote Telemetry project](https://github.com/iot-crazy/8266RemoteTelemetry)

You will already know:
1. How to use the Arduino IDE (or IDE of your choice)
2. How to upload sketches / code to your device

### Installing

1. Clone the repo to your local computer, or copy the .ino file.
2. Connect the sensors to your ESP8266 board
3. Set the WiFi network name and password in the code (around lines 9 & 10)

## Tested On

1. Heltec Wifi Kit 32

Other baords coming soon, such as the WiFi Kit 16
Please let us know if you test this on other devices so we can add to the list and acknowledge your contribution!



## Trouble Shooting

### The code does not run
1. Ensure you have selected the corect board in the Arduino IDE as "Heltec WiFi Kit 32", do not select the "Lora 32".

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

