# Make file for the HEAP Object Oriented Programing Example
# Copyright (c) 1991 By Borland International, Inc.
memtest.exe : mem.obj memtest.obj display.obj
   tlink /v memtest+mem+display

mem.obj : mem.asm vmtutil.inc mem.inc
   tasm /c /la /zi /m /DMDL=small mem.asm

memtest.obj : memtest.asm vmtutil.inc mem.inc
   tasm /c /la /zi /m /DMDL=small memtest.asm

display.obj : display.asm
   tasm /c /la /zi /m /DMDL=small display.asm

