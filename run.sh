#!/bin/sh
make clean
mkdir obj.x86/docs
/bin/cp docs/* obj.x86/docs
make
cd obj.x86
BRIE &

