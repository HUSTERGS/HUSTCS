
;   FILENAME: BIOS.INC
;
;   Copyright (c) 1988, 1990 by Borland International, Inc.
;
;   Description: This include file contains symbolic equates representing the
;   BIOS function calls and their associated services.


VIDEO_SERVICE               = 010h ; BIOS Int 10h Video Service interrupt
INT10_SET_MODE              = 000h ; set video mode
INT10_SET_CURSOR_SHAPE      = 001h ; set cursor shape
INT10_SET_CURSOR_POS        = 002h ; set cursor position
INT10_READ_CURSOR           = 003h ; get cursor position service
INT10_READ_LIGHT_PEN        = 004h ; read light pen position
INT10_SELECT_DISPLAY_PAGE   = 005h ; select display page
INT10_SCROLL_UP             = 006h ; scroll window up
INT10_SCROLL_DOWN           = 007h ; scroll window down
INT10_READ_ATTR_CHAR        = 008h ; read attribute\char
INT10_WRITE_ATTR_CHAR       = 009h ; write attribute\char
INT10_WRITE_CHAR            = 00Ah ; write character
INT10_SET_COLOR_PALETTE     = 00Bh ; set color palette
INT10_WRITE_PIXEL           = 00Ch ; write graphics pixel
INT10_READ_PIXEL            = 00Dh ; read graphics pixel
INT10_WRITE_TTY             = 00Eh ; write text in tty mode
INT10_GET_MODE              = 00Fh ; Get video display mode
INT10_SET_PALETTE_REGS      = 010h ; set palette registers
INT10_FONT_SIZE             = 011h ; determine the # of rows
INT10_WRITE_STRING          = 013h ; write string
INT10_GET_VIDEO_BUFFER      = 0FEh ; get cideo buffer
INT10_UPDATE_VIDEO_BUFFER   = 0FFh ; update video buffer

FLOPPY_SERVICE              = 013h ; Floppy disk service
INT13_RESET_FLOPPY_DISK     = 000h ; Reset the floppy disk controller
INT13_GET_SYSTEM_STATUS     = 001h ; Get the status of the floppy disk controller
INT13_READ_FLOPPY_DISK      = 002h ; Read from the floppy disk
INT13_WRITE_FLOPPY_DISK     = 003h ; Write to the floppy disk
INT13_VERIFY_DISK_SECTORS   = 004h ; Verify sectors on the disk
INT13_FORMAT_TRACK          = 005h ; Format a track on the floppy

SERIAL_PORT_SERVICE         = 014h ; BIOS serial port service
INT14_INITIALIZE_PORT       = 000h ; Initialize the COM port
INT14_WRITE_CHAR            = 001h ; Write a character to the COM port
INT14_READ_CHAR             = 002h ; Read a character from the COM port
INT14_STATUS                = 003h ; Get the COM port status

KEYBOARD_SERVICE            = 016h ; BIOS Keyboard interrupt
INT16_READ_CHAR             = 000h ; Read the next character
INT16_KBD_STATUS            = 001h ; Returns the keyboard status
INT16_KBD_FLAGS             = 002h ; Returns the keyboard flags

PRINTER_SERVICE             = 017h ; BIOS Printer interrupt
INT17_WRITE_CHAR            = 000h ; Write a character to the printer
INT17_INIT_PRINTER_PORT     = 001h ; Initialize the printer port
INT17_PRINTER_STATUS        = 002h ; Return the printer status

INT22_TERMINATE             = 022h ; Vector to terminate routine
INT23_CTRLC_HANDLER         = 023h ; Vector to CTRL-C handler
INT24_CRITICAL_ERROR        = 024h ; Vector to Critical Error handler
INT25_ABSOLUTE_READ         = 025h ; Do an absolute disk read
INT25_ABSOLUTE_WRITE        = 026h ; Do an absolute disk write
INT27_KEEP                  = 027h ; Terminate and stay resident
INT2F_PRINT_SPOOLER         = 02Fh ; Control the DOS print spooler

LIM_SERVICE                 = 067h ; Lotus/Intel/Microsoft EMS service
INT67_GET_MANAGER_STATUS    = 001h ; Test if hardware works
INT67_GET_PAGE_FRAME_SEG    = 002h ; Get the segment address of the page frame
INT67_GET_PAGE_COUNT        = 003h ; Get the number of pages
INT67_ALLOCATE_MEMORY       = 004h ; Get a handle and allocate soem memory
INT67_MAP_MEMORY            = 005h ; Map a page of memory  into the page frame
INT67_RELEADE_MEMORY        = 006h ; Release a handle and its associated memory
INT67_GET_VERSION           = 007h ; Get the version number of the manager
INT67_SAVE_CONTEXT          = 008h ; Save the mapping context
INT67_RESTORE_CONTEXT       = 009h ; Restore the mapping context
INT67_GET_HANDLE_COUNT      = 00Ch ; Get the number of handles
INT67_GET_PAGES_FOR_HANDLE  = 00Dh ; Get the numebr of pages that belong to a handle
INT67_GET_PAGES_FOR_HANDLES = 00Eh ; Get the numebr of pages that belong to each handle
INT67_GET_SET_PAGE_MAP      = 00Fh ; Get or set the settings of the page mapping hardware
