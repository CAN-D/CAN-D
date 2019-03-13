#!/bin/bash

die()
{
    echo "ERROR " $1
    exit 1
}

EXEC_DIR="`dirname \"$0\"`"
[ "$EXEC_DIR" == "." ] || die "Please execute script from ST-LINK directory"

[ -f unlock.cfg ] || die "Could not find unlock.cfg"
openocd unlock.cfg