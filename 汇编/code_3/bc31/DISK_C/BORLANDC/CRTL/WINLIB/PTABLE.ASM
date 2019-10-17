;[]-----------------------------------------------------------------[]
;|      PTABLE.ASM                                                   |
;[]-----------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1991, 1992 by Borland International
;       All Rights Reserved.
; 

            NAME    ptable

public      pLocalHeap
public      pAtomTable
public      pStackTop
public      pStackMin
public      pStackBot

pLocalHeap  EQU     00000006H
pAtomTable  EQU     00000008H
pStackTop   EQU     0000000aH
pStackMin   EQU     0000000cH
pStackBot   EQU     0000000eH
            END
