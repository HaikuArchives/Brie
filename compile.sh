#!/bin/sh
clear
make clean
make
mkdir obj.x86/docs
/bin/cp docs/* obj.x86/docs
cd obj.x86
echo Type obj.x86/BRIE to execute.
echo

