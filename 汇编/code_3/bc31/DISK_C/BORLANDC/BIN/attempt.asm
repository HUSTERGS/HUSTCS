public _dif
.386
.model flat, c
.code
_dif  proc near 
     push  ebp
     mov  ebp, esp
     mov  eax, [ebp+8]
     sub   eax, [ebp+12]
     pop   ebp
     ret
_dif  endp
     end