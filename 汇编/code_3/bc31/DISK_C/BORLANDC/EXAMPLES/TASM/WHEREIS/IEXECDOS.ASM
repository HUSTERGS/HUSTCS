
;   FILENAME: IEXECDOS.ASM
;
;   Copyright (c) 1990, 1992 by Borland International, Inc.
;
;   DESCRIPTION: This module implements the routines that handle calling
;   DOS to perform a command on each file that is found by WHEREIS.
;   This module uses ideal mode syntax.
;
;   This module looks for the location of COMMAND.COM to enable the
;   running of the commands. Since many matching files may be found,
;   and COMMAND.COM is called to execute the given DOS command for each
;   file that is found, it is best if COMMAND.COM is located in a ramdisk.
;
;   ASSEMBLY INSTRUCTIONS: To assemble this module use the following
;   TASM command line.
;
;       TASM /m /dMDL=memorymodel iparam
;
;   /m in the above command line allows TASM to resolve jumps and other
;   operations to their shortest form and get rid of extra NOPs.
;   'memorymodel' in the above command line may be replaced by TINY, SMALL,
;   MEDIUM, COMPACT, LARGE or HUGE. If assembling this module to run on
;   a 286/386 machine, turn on the P286 directive in order to take advantage of
;   286/386 specific instructions. I.E.
;
;       TASM /m /dMDL=memorymodel /jP286 iparam
;

;DO_SAMPLE_COMMAND equ 1      ; Enable this to execute a sample DIR command
;                             ;   when the command line is being parsed.

jumps

%tabsize 4

ifndef  MDL
    display "Error: This module requires that you provide a memory model"
    display "       definition on the command line. I.E. /dMDL=SMALL."
    err ; Force a fatal error
else

    ideal                           ; Use TASM's Ideal mode
%   model   MDL,pascal              ; Define the memory model

    include "dos.inc"
    include "idos.inc"
    include "kbd.inc"
    include "iwhglobl.inc"
    include "imacros.mac"

    dataseg
NO_COMMAND_GIVEN equ 0
COMMAND_GIVEN    equ 1
    DosCommandGiven   db NO_COMMAND_GIVEN

COMMAND_BUFFER_LENGTH equ 200
    ; Stores the command given on command line
    DosCommandBuffer  db COMMAND_BUFFER_LENGTH dup (?)

; The DOS command in quotes will include some special escape sequences
; that will cause the name of the file to be inserted in various ways.
;
;  %1  - The full path, filename and  extension
;  %2  - Filename and extension (no path)
;  %3  - Only the path
;  %4  - Only the filename before the extension followed by a .
;  %5  - Only the extension, preceeded by a .

    ; This is placed at the start of COMMAND.COM command strings.
    StartOfBuff       db '/C ',0

    ; Store the actual command that is executed. Any %x directives in
    ; the above command buffer are converted to their actual values
    ; as the above command is transfered into the following buffer.
    ; 32 extra bytes are an overrun buffer.
    CommandToDo       db COMMAND_BUFFER_LENGTH+32 dup (?)

    ; Needed for the call to execute COMMAND.COM
    ParamBlock        dw 7 dup (0)

    ComspecTag        db 'COMSPEC=',0

    ; Pointer into the environment block for start of COMMAND.COM location
    ComspecSeg        dw 0     ;Not changed from zero if no comspec found.
    ComspecOfs        dw ?

    MakePascalString  NoComspecMssg,<"COMSPEC= not found in environment!",13,10>

    codeseg

    ; The environment block is a group of null terminated strings.
    ; A string beginning with zero signals the end of the eviroment block.

    proc SearchEnvironment
    ;   This routine searches for a variable in the environment block.
    ;
    ;   Input
    ;       DS:SI - Points to a string like "NAME=" which is to be
    ;               found in the environment. It should be an ASCIIZ string.
    ;   Output
    ;       If the variable is found,
    ;           AL    -  0
    ;           ES:DI -  Points to string after the = sign in the environment.
    ;       If the variable is not found,
    ;           AL is nonzero.
    ;   Registers modified
    ;       all

        cld       ;Set direction for scanning to increment

        ; Set ES:DI to environment block
        push   ds
        mov    ax,@data   ; Reset to our datasegment since the "NAME="
                          ; might be in another segment.
        mov    ds,ax
        mov    es,[PspAddress]
        mov    es,[es:psp.EnvironmentBlock]
        xor    di,di
        pop    ds
    @@CheckEnvironmentEnd:
        mov    bx,si               ;initialize BX pointer to name to find
        mov    al,[byte es:di]
        or     al,al
        je     @@MatchFailed       ;jump if end is found

    @@CheckNextByte:

        mov    al,[bx]                  ;get character to match.

        or     al,al                    ;if end of name we are done!
        jz     @@MatchCompleted         ;  (AL will be zero)

        cmp    al,[byte es:di]          ;compare to char in environment block
        jne    @@FindNextString         ;jump if match failed
        inc    bx
        inc    di
        jmp    @@CheckNextByte

    @@FindNextString:
        xor    al,al                    ;scan forward in Environment Block
        mov    cx,0FFFFh                ;for zero byte.
        repnz  scasb
        jmp    @@CheckEnvironmentEnd    ;go compare next string

    @@MatchFailed:
        inc    al                       ;return al<>0 as failure flag

    @@MatchCompleted:                   ;all matched, return ES:DI pointing
                                        ; to parameter. al = 0
        ret
    endp SearchEnvironment


ifdef DO_SAMPLE_COMMAND
    ; Show a sample of the proper way to call COMMAND.COM
    dataseg
    SampleCommand db 9,'/C DIR C:',13
    codeseg
    proc SampleDosCommand
    ;   This routine calls COMMAND.COM to do the DIR command.
    ;
        mov     cx,seg SampleCommand
        mov     dx,offset SampleCommand
        call    DoDosCommand
        ret
    endp SampleDosCommand
endif

    proc DoDosCommand
    ;   This procedure executes the command string pointed at by DX:CX
    ;   by giving it to COMMAND.COM.
    ;   This routine is not reentrant because of local code segment
    ;   data storage at end of routine.
    ;
    ;   Input
    ;       None
    ;   Output
    ;       None
    ;   Calling conventions
    ;       NA
    ;   Registers modified
    ;       all

        push    ds
        mov     ax,seg ParamBlock
        mov     es,ax
        mov     bx,offset ParamBlock

        mov     [word es:bx+4],cx   ; Load the location of the command tail
        mov     [word es:bx+2],dx   ;   for the command.

        mov     [Orig_SS],SS
        mov     [Orig_SP],SP

        mov     ax,[ComSpecSeg]
        or      ax,ax
        jz      @@Skip       ; Skip over EXEC if our segment is still zero.
                             ; That means that no Comspec was found.

        mov     dx,[ComspecOfs]
        mov     ds,ax
        
        mov     ax,4b00h
        int     21h
    @@Skip:
        mov     ss,[Orig_SS]
        mov     sp,[Orig_SP]
        pop     ds
        ret

    ; Preserves the location of our stack.
    Orig_SS dw ?
    Orig_SP dw ?
    endp DoDosCommand

    proc ParseDosCommand
    ;   This procedure initializes all variables and data structures
    ;   used for executing the DOS command.
    ;
    ;   Input
    ;       ES:DI - Points to DOS command which is surrounded by quotes.
    ;               It is a pascal style string
    ;   Output
    ;       Carry set if a command has already been specified
    ;   Calling conventions
    ;       NA
    ;   Registers modified
    ;       all

        cmp     [DosCommandGiven],COMMAND_GIVEN
        jne     @@FirstUse
        stc     ; An error because a command was already specified
        jmp     @@Exit

    @@FirstUse:
        push    es di           ; Preserve pointer to DOS command
        ; We need to find COMMAND.COM before we can know that we can
        ; do a DOS command.
         mov    si,offset ComspecTag     ;DS:SI string to match
         call   SearchEnvironment        ;go search environment
         or     al,al
         jne    ComspecNotFound

         mov    [ComspecSeg],es          ; If it was found, ES:DI is stored.
         mov    [ComspecOfs],di
         jz     FreeExtraMemory

    ComspecNotFound:
         call   WritePascalString,ds,offset NoComspecMssg

    FreeExtraMemory:
        ; We need to give up extra memory.
        mov     bx,zzzzzseg     ; Location of first segment of free memory
        mov     ax,[PspAddress] ; PSP segment
        sub     bx,ax           ; BX now contains paragraphs used
                                ;   by this program.
        mov     es,ax
        mov     ah,4ah
        int     21h

ifdef DO_SAMPLE_COMMAND
        call    SampleDosCommand
endif
        pop     di es           ; Restore pointer to DOS command

        ; Check if the final character is a quote and
        ;   remove it if it is.
        xor     bh,bh           ; Get length of string in BX
        mov     bl,[es:di]

        mov     al,[es:di+bx]   ; Load last character of string
        call    IsDelimiter
        jnc     RemoveLeadingQuote

    RemoveTrailingQuote:
        dec     [byte ES:DI]    ; Remove the trailing delimiter

    RemoveLeadingQuote:
        push    es di           ; Preserve the location of the DOS command
        mov     cx, 1           ; Remove the first character
        mov     ax, 1           ; from the string
        call    DeleteChar,es,di
        pop     di es           ; Restore the location

        ; Copy the command to the DOS command buffer
        xor     ah,ah
        mov     al,[byte es:di]
        inc     ax

        call    ByteCopy,es,di,seg DosCommandBuffer,Offset DosCommandBuffer

        ; Set flag so we know that a command was given.
        mov     [DosCommandGiven],COMMAND_GIVEN
        clc     ; No error
    @@Exit:
        ret
    endp ParseDosCommand


    dataseg
    ; Local data area for ExecuteDosCommand

    ; The following act as pointers to the data for this invocation of
    ; ExecuteDosCommand.
    DirectoryPath dw ?
    FileNameSeg   dw ?
    FileName      dw ?

    codeseg
    proc ExecuteDosCommand
    ;   This procedure actual executes the DOS command, if given, for
    ;   each file that is found.
    ;
    ;   Input
    ;       ax:si - Offset of filename
    ;       di - offset of currentdir
    ;   Output
    ;       none
    ;   Calling conventions
    ;       NA
    ;   Registers modified
    ;       all except es

        mov     [DirectoryPath],di
        mov     [FileNameSeg],ax
        mov     [FileName],si

        push    es
        cmp     [DosCommandGiven],COMMAND_GIVEN
        jne     @@Exit

        ; Blank out the buffer for the command to do.
        cld     ; Autoincrement
        mov     ax,seg CommandToDo
        mov     es,ax
        mov     di,offset CommandToDo
        mov     cx,COMMAND_BUFFER_LENGTH
        mov     al,0
        rep stosb

        ; We need to go into a loop of copying from the input command
        ; string until we find a %

        mov     di,offset CommandToDo        ; For results            es:di
        xor     cl,cl                        ; Length of output string
        inc     di                           ; Move over the leading length byte

        mov     si,offset StartOfBuff
        call    CopyAsciizString             ; Copy the starting /C

        mov     si,offset DosCommandBuffer   ; For original command   ds:si
        mov     ch,[si]                      ; Length of original string
        inc     si                           ; Move over the leading length byte


    @@ProcessChar:
        or      ch,ch
        jz      SourceExhausted
        lodsb                   ; Load current byte
        dec     ch              ; One less character to get

        cmp     al,'%'
        je      @@ProcessSpecial
    @@EmitChar:
        stosb                   ; This route handles regular characters
        inc     cl              ; Increment length of output string
        cmp     cl,COMMAND_BUFFER_LENGTH-1
        jae     SourceExhausted ; Force early termination if we run out of room!
        jmp     @@ProcessChar

    @@ProcessSpecial:           ; We saw a % sign.
        or      ch,ch
        jz      @@EmitChar      ;Output because there is nothing more after it
        lodsb
        dec     ch
        ; Try to recognize one of the %x directives:
        cmp     al,'1'
        je      Process1
        cmp     al,'2'
        je      Process2
        cmp     al,'3'
        je      Process3
        cmp     al,'4'
        je      Process4
        cmp     al,'5'
        je      Process5

        ; We don't recognize it, so output the %x unchanged.
        mov     [byte es:di],'%'  ; Put out the % that got us here
        inc     cl                ; Increment length of output string
        inc     di
        jmp     @@EmitChar        ; Output the character in AL


    Process1:
        call    EmitPath
        cmp     cl,COMMAND_BUFFER_LENGTH-1
        jae     SourceExhausted ; Force early termination if we run out of room!
    Process2:
        call    EmitFileRoot
        cmp     cl,COMMAND_BUFFER_LENGTH-1
        jae     SourceExhausted ; Force early termination if we run out of room!
        jmp     Process5

    Process3:
        call    EmitPath
        jmp     @@ProcessChar

    Process4:
        call    EmitFileRoot
        call    EmitDot
        jmp     @@ProcessChar

    Process5:
        Call    EmitDot
        call    EmitExtension
        jmp     @@ProcessChar

    SourceExhausted:
        ;We need to fill in the length byte, along with a 13 at the end.
        mov     al,13
        stosb
        mov     [CommandToDo],cl     ; Fill in the length byte

        mov     cx,seg CommandToDo
        mov     dx,offset CommandToDo
        call    DoDosCommand

    @@Exit:
        pop     es
        ret
    endp ExecuteDosCommand



    proc EmitPath
    ; This routine writes the drive and path to the output command.com string

        push    si ds

        mov     si,offset Drive
        call    CopyPascalString

        mov     si,[DirectoryPath]
        cmp     [byte ds:si],'A'
        jl      @@NoBackSlash
        dec     si
    @@NoBackSlash:
        call    CopyAsciizString

        mov     ax,seg SwitchChar
        mov     ds,ax
        mov     si,offset SwitchChar
        call    CopyPascalString

        pop     ds si
        ret
    endp EmitPath



    proc EmitFileRoot
    ; This routine writes the part of the filename that is before the
    ; extension to the output string that will be sent to COMMAND.COM

        push    si ds
        mov     si,[FileName]
        mov     ax,[FileNameSeg]
        mov     ds,ax

        mov     al,'.'
        call    CopyTerminatedString
        pop     ds si
        ret
    endp EmitFileRoot



    proc EmitExtension
    ; This routine writes the extension of the current file to the
    ; output string that will be sent to COMMAND.COM

        push    si ds
        mov     si,[FileName]
        mov     ax,[FileNameSeg]
        mov     ds,ax

        mov     al,'.'
    @@CheckAgain:
        mov     ah,[ds:si]
        cmp     ah,al
        je      @@DotFound
        or      ah,ah
        jz      @@Exit       ; Quit searching if a zero is found
        inc     si
        jmp     @@CheckAgain
    @@DotFound:
        inc     si
        call    CopyAsciizString
    @@Exit:
        pop     ds si
        ret
    endp EmitExtension



    proc EmitDot
    ; This routine outputs a . to the string to be sent to command.com.

        mov     [byte es:di],'.'  ; Put out the .
        inc     cl
        inc     di
        ret
    endp EmitDot


    ; The following string copy routines are special for this module.
    ; DS:SI point to the source string. (DS:SI are preserved.)
    ; ES:DI Point to the destination string area. (ES:DI is not preserved.)
    ; CL is updated for every byte output to ES:DI.

    proc CopyPascalString
    ; Copy pascal type string to ES:DI, but omit the length byte.
        xor     bx,bx
        mov     al,[ds:si]
        add     cl,al

    @@CopyChar:
        mov     ah,[ds:si+1+bx]
        mov     [es:di],ah
        inc     di
        inc     bx
        dec     al
        jnz     @@CopyChar

        ret
    endp CopyPascalString



    proc CopyAsciizString
    ; Copy a string that is terminated by a zero.
        xor     al,al
        call    CopyTerminatedString
        ret
    endp CopyAsciizString



    proc CopyTerminatedString
    ; Copy a string terminated by any character.
    ; al contains character to stop copy. Normally 0 for ASCIIZ strings
    ; Note that the terminator is not copied.
        xor     bx,bx

    @@CopyMoreChar:
        mov     ah,[ds:si+bx]
        cmp     ah,al
        jz      @@AtEnd
        mov     [es:di],ah
        inc     di
        inc     bx
        inc     cl
        jnz     @@CopyMoreChar
    @@AtEnd:
        ret
    endp CopyTerminatedString






segment zzzzzseg   ; Dummy final segment for calculating program size
                   ; to release memory back to DOS.
ends    zzzzzseg

endif   ; ifndef MDL

end


