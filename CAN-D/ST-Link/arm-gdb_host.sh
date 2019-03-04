#!/bin/bash

PORT=4422
ELF=""

setup()
{
  shopt -s nullglob

  files=( *.elf )
  if [ ${#files[@]} -gt 1 ]; then
    echo "Found more than one elf file. Exiting..."
    return 1
  fi
  if [ ${#files[@]} -eq 0 ]; then
    echo "No elf file found. Exiting..."
    return 1
  fi

  ELF=${files[0]}
  echo "Using ${ELF}"

  return 0
}

setup
/usr/bin/expect ../ST-Link/arm-gdb_load ${ELF}
exit 0

