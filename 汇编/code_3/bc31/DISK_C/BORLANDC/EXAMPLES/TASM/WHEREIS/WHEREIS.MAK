# Make file for Turbo Assembler  WHEREIS sample project.
#   Copyright (c) 1988, 1992 by Borland International, Inc.

# The WHEREIS example takes advantage of many special TASM features.
TASM_OPTIONS = /zi /dMDL=small /m # Options for TASM

whereis.exe : iwhereis.obj iparam.obj ifindbyt.obj\
              ibytecpy.obj ifindrep.obj ilocstrg.obj\
              iwriteps.obj iskpwhit.obj iasciizs.obj\
              iparsefn.obj ifindfil.obj idelchar.obj\
              iexecdos.obj
  \tlink /v iwhereis+iparam+ifindbyt+\
        ibytecpy+ifindrep+ilocstrg+iwriteps\
        +iskpwhit+iasciizs+iparsefn+ifindfil+idelchar+iexecdos
  del whereis.exe
  ren iwhereis.exe whereis.exe

.ASM.OBJ :
  tasm $(TASM_OPTIONS) $*

iwhereis.obj : iwhereis.asm iwhglobl.inc kbd.inc dos.inc whusage.inc\
               imacros.mac bios.inc ibios.mac idos.mac
  tasm $(TASM_OPTIONS) iwhereis

iexecdos.obj : iexecdos.asm idos.mac dos.inc imacros.mac ibios.mac bios.inc
  tasm $(TASM_OPTIONS) iexecdos

iwriteps.obj : iwriteps.asm idos.mac dos.inc imacros.mac ibios.mac bios.inc
  tasm $(TASM_OPTIONS) iwriteps

ifindfil.obj : ifindfil.asm iwhglobl.inc idos.mac idos.inc ibios.mac\
               imacros.mac bios.inc kbd.inc dos.inc
  tasm $(TASM_OPTIONS) ifindfil

iasciizs.obj : iasciizs.asm ibios.mac imacros.mac bios.inc idos.mac dos.inc
  tasm $(TASM_OPTIONS) iasciizs

iparam.obj : iparam.asm iwhglobl.inc dos.inc idos.inc kbd.inc
  tasm $(TASM_OPTIONS) iparam

ibytecpy.obj : ibytecpy.asm imacros.mac ibios.mac bios.inc
  tasm $(TASM_OPTIONS) ibytecpy

ilocstrg.obj : ilocstrg.asm imacros.mac ibios.mac bios.inc
  tasm $(TASM_OPTIONS) ilocstrg

iskpwhit.obj : iskpwhit.asm kbd.inc
  tasm $(TASM_OPTIONS) iskpwhit
