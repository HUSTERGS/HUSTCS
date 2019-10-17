; Turbo Assembler    Copyright (c) 1988, 1991 By Borland International, Inc.

; PRIMES.ASM

;
; Sample 80386 code to calculate all primes between
; 0 and a specified value (inclusive).
;
; Input (assumes a large far call, with 6 bytes of return address
; pushed on the stack):
;
;    ESP+06h on entry (last parameter pushed) - the 
;    doubleword value of the maximum number to be checked as
;    to whether it is a prime.
;
;    ESP+0Ah on entry (first parameter pushed) - a large far
;    (6 byte offset) pointer to the table in which to store a
;    1 at the offset of each number that is a prime and a 0 at
;    the offset of each number that is not a prime. The table
;    must be at least [ESP+06h]+1 bytes in length, where
;    [ESP+06h] is the other parameter.
;
; Output: None
;
; Registers destroyed:
;    EAX, EBX, EDX, EDI
;
; Based on an algorithm presented in "Environments,"
; by Charles Petzold, PC Magazine, Vol. 7, No. 2.
;
     .386

Code_Seg   SEGMENT   USE32
     ASSUME    CS:Code_Seg
CalcPrimes     PROC FAR
     push es                             ;save caller's ES
     push fs                             ;save caller's FS
;
; Get parameters.
;
     mov  ecx,[esp+4+06h]
     lfs  edx,[esp+4+0ah]
;
; Assume all numbers in the specified range are primes.
;
     push fs
     pop  es                             ;point ES to table's
                                         ;segment
     mov  al,1
     mov  edi,edx
     cld
     push ecx                            ;save maximum number to
                                         ;check
     inc  ecx                            ;set up to maximum
                                         ;number, inclusive
     rep  stosb
     pop  ecx                            ;get back maximum number
                                         ;to check
;
; Now eliminate all numbers that aren't primes by calculating all
; multiples (other than times 1) less than or equal to the
; maximum number to check of all numbers up to the maximum number
; to check
;
     mov  eax,2                          ;start with 2, since 0 &
                                         ;1 are primes,
                                         ; and can't be used for
					 ;elimination of
                                         ; multiples
PrimeLoop:
     mov  ebx,eax                        ;base value to calculate
                                         ;all multiples of
MultipleLoop:
     add  ebx,eax                        ;calculate next multiple
     cmp  ebx,ecx                        ;have we checked all
                                         ;multiples of this
                                         ; number?
     ja   CheckNextBaseValue             ;yes, go to next number
     mov  BYTE PTR fs:[edx+ebx],0        ;this number is not
                                         ;prime, since
                                         ; it's a multiple of
					 ;something
      jmp MultipleLoop                   ;eliminate the next
                                         ;multiple
CheckNextBaseValue:
      inc eax                            ;point to next base
                                         ;value (the
                                         ; next value to
					 ;calculate all
                                         ; multiples of)
      cmp eax,ecx                        ;have we eliminated all
                                         ;multiples?
      jb  PrimeLoop                      ;no, check the next set
                                         ;of multiples
      pop fs                             ;restore caller's FS
      pop es                             ;restore caller's ES
      ret
CalcPrimes     ENDP
Code_Seg       ENDS
           END
