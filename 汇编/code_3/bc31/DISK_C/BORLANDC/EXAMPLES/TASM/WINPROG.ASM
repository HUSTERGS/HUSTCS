; Turbo Assembler    Copyright (c) 1988, 1991 By Borland International, Inc.

; WINPROG.ASM - Template for writing windows programs

; From the Turbo Assembler Users Guide

MULTIPLE_INST = 0       ;set to 1 to allow multiple instances of
                        ; the program, 0 otherwise.

P286                    ;select pertinent processor
WARN PRO                ;enable Turbo Assembler's checking for
                        ; protection violations that can be caught
                        ; at assembly time

MODEL      SMALL        ;other models are allowed
INCLUDELIB SLIBCEW      ;library must be appropriate for model

;Include the standard library for Windows
INCLUDELIB LIBW
EXTRN C _ACRTUSED:ABS   ;forces inclusion of the library

;Enable local symbols
LOCALS

;Include files
INCLUDE WINDOWS.INC   ;contains definitions for Windows data types,etc.
INCLUDE WINPROG.INC   ;user-defined include file for user messages,etc.

;External windows procedures
;All windows functions used must be declared as external
EXTRN PASCAL LoadIcon:FAR          ;get a pointer to an icon
EXTRN PASCAL LoadCursor:FAR        ;get a pointer to a cursor
EXTRN PASCAL GetStockObject:FAR    ;get brush handle
EXTRN PASCAL RegisterClass:FAR     ;register a window class
EXTRN PASCAL CreateWindow:FAR      ;create a window
EXTRN PASCAL ShowWindow:FAR        ;enable window
EXTRN PASCAL UpdateWindow:FAR      ;force a draw
EXTRN PASCAL GetMessage:FAR        ;get next message
EXTRN PASCAL DispatchMessage:FAR   ;dispatch message
EXTRN PASCAL DefWindowProc:FAR     ;process message in default manner
EXTRN PASCAL PostQuitMessage:FAR   ;quit
EXTRN PASCAL BeginPaint:FAR        ;begin paint request
EXTRN PASCAL EndPaint:FAR          ;end paint request
EXTRN PASCAL TextOut:FAR           ;display text

;Our DLL function
EXTRN PASCAL SetHello:FAR          ;DLL function

DATASEG
lpszClass  db 'GenericWClass',0    ;class name of windows used by
                                   ; application
lpszTitle  db 'Generic Sample Assembly Application',0
                                   ;title of the application
lpszMenu   db 'GenericMenu',0      ;default menu title

;<<Other initialized data goes here>>

UDATASEG
hInstance  dw ?                    ;current instance handle

;<<Other uninitialized data goes here>>

CODESEG
;[Main Application Windows procedure]
;Execution starts here!
;Returns AX=0 if initialization was unsuccessful
WinMain PROC WINDOWS PASCAL
PUBLIC PASCAL WinMain
ARG @@hInstance:WORD,              \Handle to this instance
    @@hPrevInstance:WORD,          \Handle to previous instance
    @@lpszCmd:DWORD,               \Pointer to command line
    @@nShow:WORD                   ;value to pass to ShowWindow
USES ES,SI,DI
UDATASEG
    @@msg msgstruct ?              ;message storage
    @@wc wndclass ?                ;window class structure
CODESEG
IF MULTIPLE_INST EQ 0
   CMP @@hPrevInstance,0
   JZ @@ok
   XOR AX,AX
   RET
@@ok:
ENDIF
   MOV AX,@@hInstance
   MOV hInstance,AX

   ;Initialize window class structure.
   ;These parameters may change based on your preferences
   MOV @@wc.clshInstance,AX
   XOR AX,AX
   MOV WORD PTR @@wc.clslpfnWndProc,OFFSET MainMsgProc
   MOV WORD PTR @@wc.clslpfnWndProc+2,CS
   MOV WORD PTR @@wc.clslpszClassName,OFFSET lpszClass
   MOV WORD PTR @@wc.clslpszClassName+2,DS
   MOV WORD PTR @@wc.clslpszMenuName,OFFSET lpszMenu
   MOV WORD PTR @@wc.clslpszMenuName+2,DS
   MOV @@wc.clsStyle,AX
   MOV @@wc.clscbClsExtra,AX
   MOV @@wc.clscbWndExtra,AX
   CALL LoadIcon PASCAL,AX,AX IDI_APPLICATION
   MOV @@wc.clshIcon,AX
   XOR AX,AX
   CALL LoadCursor PASCAL,AX,AX IDC_ARROW
   MOV @@wc.clshCursor,AX
   CALL GetStockObject PASCAL,WHITE_BRUSH
   MOV @@wc.clshbrBackground,AX

   ;Register class
   CALL RegisterClass PASCAL,DS OFFSET @@wc

   ;Now create window.
   ;This uses default parameters; your preferences may vary.
   XOR  AX,AX
   MOV  BX,CW_USEDEFAULT
   CALL CreateWindow PASCAL,DS OFFSET lpszClass,DS OFFSET lpszTitle,\
        WS_OVERLAPPEDWINDOW AX,\
        BX,BX,BX,BX,\
        AX,AX,hInstance,AX AX

   ;AX is the window descriptor. Display window and update it.
   PUSH AX
   CALL ShowWindow PASCAL,AX,@@nShow
   POP AX
   CALL UpdateWindow PASCAL,AX

   ;Message handler loop.
@@LUP: CALL GetMessage PASCAL,DS OFFSET @@msg,0,0,0
   AND AX,AX
   JZ @@RET
   CALL DispatchMessage PASCAL,DS OFFSET @@msg
   JMP @@LUP
@@RET:                           ;no more messages
   MOV AX,-1
@@QUIT: RET
WinMain ENDP

;----------------------------------------------------------------------
;Main message-handling procedure
;An address to this procedure is passed to Windows during
;initialization portion of WinMain.
;This works by scanning the message dispatch table for a matching;message, and calling the appropriate handler. If message is not
;present in handler table, it is passed back to Windows to handle.
;Returns a value in DX:AX that is 0 if message was handled.
;----------------------------------------------------------------------
MainMsgProc PROC WINDOWS PASCAL FAR
PUBLICDLL PASCAL MainMsgProc
ARG @@hwnd:WORD,                 \Window descriptor
    @@message:WORD,              \ID of message
    @@wParam:WORD,               \Additional word
    @@lParam:DWORD               ;additional dword
USES ES,SI,DI

DATASEG

;Table of messages this procedure will handle.

;This structure represents an entry in a message table.
@@MsgRec  STRUC
@@MsgType DW 0                   ;message ID
@@MsgProc DW ?                   ;procedure address
@@MsgRec  ENDS

;Add to these as you wish.
@@MsgTable LABEL @@MsgRec
   @@MsgRec {@@MsgType=WM_DESTROY,  @@MsgProc=DestroyWindow}
   @@MsgRec {@@MsgType=WM_PAINT,    @@MsgProc=PaintWindow}
   @@MsgRec {@@MsgType=IDM_ABOUT,   @@MsgProc=DoAbout}
   @@MsgRec {}	;Terminate the list

CODESEG

   ;Dispatch based on message type.
   MOV SI,OFFSET @@MsgTable
@@LP: MOV AX,[SI.@@MsgType]
   AND AX,AX
   JZ @@NF
   CMP AX,@@message
   JZ @@FD
   ADD SI,SIZE @@MsgRec
   JMP SHORT @@LP
@@FD:                     ;found; call routine to handle message
   CALL [SI.@@MsgProc] PASCAL,@@hwnd,@@wParam,@@lParam
   XOR AX,AX
   XOR DX,DX
   RET
@@NF:                     ;not found; take default action
   CALL DefWindowProc PASCAL,@@hwnd,@@message,@@wParam,@@lParam
   ;Return whatever the default handler returns
   RET
MainMsgProc ENDP

;----------------------------------------------------------------------
;These are the routines to handle messages.
;These message-handling routines are NEAR PASCAL procedures that take
;as arguments the window handle, and the word and dword param from
;the message.
;New message-handling routines should be added here.
;----------------------------------------------------------------------

;Process WM_DESTROY message
;Closes the window.
DestroyWindow PROC PASCAL NEAR
ARG @@hwnd:WORD,                   \Window descriptor
    @@wParam:WORD,                 \Word parameter
    @@lParam:DWORD                 ;dword parameter
    CALL PostQuitMessage PASCAL,0
    RET
DestroyWindow ENDP

;Process WM_PAINT message
;Repaints the window.
;(This demonstrates use of the SetHello DLL routine)
PaintWindow PROC PASCAL NEAR
ARG @@hwnd:WORD,                   \Window descriptor.
    @@wParam:WORD,                 \Word parameter
    @@lParam:DWORD                 ;dword parameter
LOCAL @@hdc:WORD                   ;handle to device context
UDATASEG
   @@ps   PAINTSTRUCT ?
   @@text db 80 dup (?)
CODESEG
   CALL BeginPaint PASCAL,@@hwnd,DS OFFSET @@ps
   MOV @@hdc,AX
   CALL SetHello PASCAL,DS OFFSET @@text
   SUB BX,BX
   CALL TextOut PASCAL,@@hdc,BX,BX,DS OFFSET @@text,AX
   CALL EndPaint PASCAL,@@hwnd,DS OFFSET @@ps
   RET
PaintWindow ENDP

;Process IDM_ABOUT message.
;Display the "About..." box.
DoAbout PROC PASCAL NEAR
ARG @@hwnd:word,                   \Window descriptor
    @@wParam:word,                 \Word parameter
    @@lParam:dword                 ;dword parameter
;<<Your ABOUT stuff goes here>>
RET
DoAbout ENDP
END
