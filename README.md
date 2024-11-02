# Setup / Configure

copy to your project:  `/pico/pico-sdk/external/pico_sdk_import.cmake`

Setup a `CMakeLists.txt`

Wokwi supports `hex` and `uf2`
Board	            Supported firmware types
Raspberry Pi Pico	.hex, .uf2

## Vscode linting
The include path shoudl already have ``.
Add `${env:PICO_SDK_PATH}/**` .
Note in the GUI, every include is a new line
[.vsode setup](https://stackoverflow.com/a/74407294/1586821)