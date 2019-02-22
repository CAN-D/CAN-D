# Flashing and debugging the board

## Easy Way:

### Windows 
Download and use the ST-Link Utility: https://www.st.com/en/development-tools/stsw-link004.html.

### macOS and Linux
Intall the open source ST-Link tool and use GDB. Follow these instructions https://github.com/texane/stlink.

## Hard Way 
### macOS and Linux

If your device is write protected, you may need to use openOCD in place of the ST-Link tool. In that case, `brew install openocd` and run the command `openocd -f stlink-v2.cfg`. This will start a openocd server to which you can connect a remote GDB session (see the instructions in the [texane/stlink](https://github.com/texane/stlink) repo).