#!/bin/bash

die()
{
    echo "ERROR " $1
    exit 1
}

EXEC_DIR="`dirname \"$0\"`"
[ "$EXEC_DIR" == "." ] || die "Please execute script from ST-LINK directory"

echo "Erasing Write Protection..."

./remove_write_protect.sh

[ -d "../build" ] || die "Could not find build directory"
cd ../build

echo "Flashing CAN-D Device..."

# Create hex file of our elf
arm-none-eabi-objcopy -O ihex *.elf ./CAN-D.hex

# Flash the CAN-D board
st-flash --format ihex write CAN-D.hex