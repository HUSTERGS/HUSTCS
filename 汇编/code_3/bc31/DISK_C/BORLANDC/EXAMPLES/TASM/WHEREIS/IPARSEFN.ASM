
;   FILENAME: IPARSEFN.ASM
;
;   Copyright (c) 1988, 1992 by Borland International, Inc.
;
;   DESCRIPTION:  This module implements a routine that parses a file spec.
;   into its drive, path and file name.
;
;   ASSEMBLY INSTRUCTIONS: To assemble this module use the following
;   TASM command line.
;
;       TASM /dMDL=memorymodel iparsefn
;
;   'memorymodel' in the above command line may be replaced by TINY, SMALL,
;   MEDIUM, COMPACT, LARGE or HUGE.

%tabsize 4

ifndef  MDL
    display "Error: This module requires that you provide a memory model"
    display "    definition on the command line. I.E. /dMDL=SMALL."
    err ; Force a fatal error
else

    ideal                   ; Use TASM's Ideal mode
%   model   MDL             ; Define the memory model

    codeseg

    global  ParseFilename:proc      ; Declare a public proc

    global  FindBytePos:proc        ; Declare extrn proc's
    global  ByteCopy:proc
    global  GetASCIIZStrLen:proc

    proc    ParseFilename

    ;   This routine takes a pointer to a FileSpecification and returns three
    ;   pointers to the filenames drive, path and FileSpecification. Note
    ;   that the space to store the drive, path and FName must be allocated
    ;   by the calling routine. The three strings generated are stored as
    ;   pascal strings. That is, with a leading length byte. The original
    ;   FileSpecification spec. is assumed to be stored as an ASCIIZ string.
    ;
    ;   Input
    ;       FileSpecification - Far pointer to the complete FileSpecification
    ;       Drive    - Far pointer to location to store the drive
    ;       Path     - Far pointer to location to store the path
    ;       FName    - Far pointer to location to store the FileSpecification
    ;   Output
    ;       The var parameters Drive, Path and FName point to the parsed
    ;       components of the FileSpecification.
    ;   Calling conventions
    ;       Pascal
    ;   Registers modified
    ;       ax, bl, cx, es, di

    arg FName:dword, Path:dword, Drive:dword, FileSpecification:dword

        push    bp
        mov     bp, sp

        ; First initialize the length bytes of each of the drive and path

        les     di, [Drive]
        mov     [byte es:di], 0
        les     di, [Path]
        mov     [byte es:di], 0
        mov     al, ':'             ; Search for the colon indicating a drive
        mov     cx, 3               ; definition
        push    [word FileSpecification+2]   ; Push the address of the FileSpecification
        push    [word FileSpecification]
        mov     si, sp
        inc     [word ss:si]
        call    FindBytePos         ; Look for the ':'
        jcxz    FindEndOfPath
        les     di, [Drive]
        mov     [byte es:di], al    ; Store the length of the drive definition
        xor     ah, ah
        push    [word FileSpecification+2]   ; Push the address of the FileSpecification
        push    [word FileSpecification]
        mov     si, sp
        inc     [word ss:si]
        push    [word Drive+2]      ; Push the address to store the drive
        push    [word Drive]        ; definition in
        inc     [word ss:si-4]
        call    ByteCopy            ; Copy the drive spec.
    FindEndOfPath:
        les     di, [Drive]         ; Get the address of the drive description
        xor     bx, bx
        mov     bl, [byte es:di]    ; Get the length of the drive spec.
        les     di, [FileSpecification] ; Get the address of the FileSpecification
        mov     cl, [byte es:di]    ; Get the length of FileSpecification
        inc     di                  ; Skip length byte
        add     di, bx              ; Move the pointer past the drive spec.
        sub     cl, bl              ; subtract the length of the drive spec.
        push    es                  ; Save the pointer to the start of the path
        push    di
    NextBackSlash:
        push    es                  ; Save the current pointer
        push    di
        push    es                  ; Pass the current pointer to FindBytePos
        push    di
        mov     al, '\'             ; Look for backslash
        call    FindBytePos         ; Find the next '\' character
        jcxz    CopyPath            ; Didn't find a '\'
        pop     bx                  ; Remove the pointer to the last '\' from
        pop     bx                  ; the stack.
        jmp     NextBackSlash
    CopyPath:
        mov     si, sp
        mov     ax, [ss:si]         ; Get offset to last character in path
        mov     bx, [ss:si+4]       ; Get offset to first position of path
        sub     ax, bx              ; Determine the length of the string to copy
        jz      NoPath
        push    [ss:si+6]           ; Push the address of the start of the
        push    [ss:si+4]           ; path for the call to ByteCopy
        push    [word Path+2]       ; Push the destination to copy the path to.
        push    [word Path]
        mov     si, sp
        inc     [word ss:si]        ; Point past the length byte
        call    ByteCopy
        les     di, [Path]
        mov     [byte es:di], al    ; Store the length byte
    NoPath:

        ; At this point a pointer to the start of the path and a pointer to
        ; the end of the path(i.e. the start of the FileSpecification) are still
        ; on the stack.

        les     di, [FileSpecification] ; Determine the length of the filename
        mov     al, [byte es:di]        ; part of FileSpecification
        les     di, [Path]
        sub     al, [byte es:di]
        les     di, [Drive]
        sub     al, [byte es:di]

        ; Now use the pointer to the filename(still on the stack) in the call
        ; to ByteCopy and copy the filename to its storage location.

        push    [word FName+2]      ; Push the address to store the filename
        push    [word FName]
        mov     si, sp              ; Skip the length byte in the destination
        inc     [byte ss:si]        ; string
        les     di, [FName]
        mov     [byte es:di], al    ; Store the length byte
        call    ByteCopy
        pop     bx                  ; Claen up the stack
        pop     bx
        pop     bp
        ret                         ; Don't remove any of the parameters from
                                    ; the stack as they are var parameters.
    endp    ParseFilename

endif   ; ifndef MDL

end
