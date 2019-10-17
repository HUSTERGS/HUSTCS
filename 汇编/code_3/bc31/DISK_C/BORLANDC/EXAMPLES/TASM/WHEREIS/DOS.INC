
;   FILENAME: DOS.INC
;
;   Copyright (c) 1988, 1990 by Borland International, Inc.
;
;   Description: This include file contains symbolic equates representing the
;   DOS function calls and their associated services.

DOS_FUNCTION            = 021h ; Dos Function call
STDOUT                  = 001h ; File handle for Standard Output device
STDERR                  = 002h ; File handle for Standard Error device

DOS_PROGRAM_TERMINATE   = 000h ; Terminate the program
DOS_READ_KBD_ECHO       = 001h ; Read the keyboard and echo to the screen
DOS_WRITE_CHARACTER     = 002h ; Output a character
DOS_AUXILIARY_INPUT     = 003h ; Read character from auxiliary device
DOS_AUXILIARY_OUTPUT    = 004h ; Write a character to the auxiliary device
DOS_PRINTER_OUTPUT      = 005h ; Send character to standard list device
DOS_CONSOLE_IO          = 006h ; Console Input/Output
DOS_UNFILTERED_INPUT    = 007h ; Unfiltered character input without echo
DOS_CHARACTER_INPUT     = 008h ; Character input without echo
DOS_WRITE_STRING        = 009h ; Display a '$' terminated string
DOS_BUFFERED_INPUT      = 00Ah ; Read text and store it in a buffer
DOS_GET_INPUT_STATUS    = 00Bh ; Check if input is available
DOS_RESET_INPUT         = 00Ch ; Clear the input buffer and check for input
DOS_DISK_RESET          = 00Dh ; Flush all DOS file buffers to disk
DOS_CHANGE_DISK_DRIVE   = 00Eh ; Set the default disk drive
DOS_OPEN_FCB_FILE       = 00Fh ; Open a file using FCB's
DOS_CLOSE_FCB_FILE      = 010h ; Close a file that uses FCB's
DOS_FIND_FIRST_FCB      = 011h ; Search for the first matching file
DOS_FIND_NEXT_FCB       = 012h ; Find the next matching file
DOS_DELETE_FCB_FILE     = 013h ; Delete a file using FCB's
DOS_SEQUENTIAL_READ     = 014h ; Reads the next block from a fil
DOS_SEQUENTIAL_WRITE    = 015h ; Writes the next block of data to a file
DOS_CREATE_FCB_FILE     = 016h ; Create and/or open a file for i/o
DOS_RENAME_FCB_FILE     = 017h ; Rename a file using FCB's
DOS_GET_DISK_DRIVE      = 019h ; Get the current disk drive
DOS_SET_DTA             = 01Ah ; Set the Disk Transfer Area address
DOS_DEFAULT_DRIVE_INFO  = 01Bh ; Get allocation information for the default drive
DOS_DRIVE_INFO          = 01Ch ; Get allocation information for a specific drive
DOS_RANDOM_READ         = 021h ; Perform a random file read
DOS_RANDOM_WRITE        = 022h ; Perform random file write
DOS_GET_FILE_SIZE       = 023h ; Get file size in records
DOS_SET_RECORD_NUMBER   = 024h ; Set the random record number
DOS_SET_VECTOR          = 025h ; Set an interrupt vector
DOS_CREATE_PSP          = 026h ; Create a Program Segment Prefix(PSP)
DOS_RANDOM_BLOCK_READ   = 027h ; Random block read of a file
DOS_RANDOM_BLOCK_WRITE  = 028h ; Random block write to a file
DOS_PARSE_FILENAME      = 029h ; Parse a filename
DOS_GET_DATE            = 02Ah ; Get the DOS Date
DOS_SET_DATE            = 02Bh ; Set the DOS Date
DOS_GET_TIME            = 02Ch ; Get the DOS Time
DOS_SET_TIME            = 02Dh ; Set the DOS Time
DOS_SET_VERIFY_FLAG     = 02Eh ; Set the DOS verify flag
DOS_GET_DTA             = 02Fh ; Get the DTA address
DOS_GET_DOS_VERSION     = 030h ; Get the MS-DOS Version #
DOS_KEEP                = 031h ; Terminate and stay resident
DOS_GET_SET_CTRL_BREAK  = 033h ; Get or set the Ctrl-Break flag
DOS_GET_VECTOR          = 035h ; Get the interrupt vector
DOS_GET_DISK_SPACE      = 036h ; Returns allocation info. about a disk
DOS_GET_SET_COUNTRY     = 038h ; Get or set the current info. about the country
DOS_MAKE_DIRECTORY      = 039h ; Create a directory
DOS_DELETE_DIRECTORY    = 03Ah ; Delete a directory
DOS_SET_CURRENT_DIR     = 03Bh ; Set the current directory
DOS_CREATE_FILE         = 03Ch ; Create or truncate a file
DOS_OPEN_FILE           = 03Dh ; Open an existing file
DOS_CLOSE_FILE          = 03Eh ; Close a file
DOS_READ_FROM_HANDLE    = 03Fh ; Read from DOS file handle
DOS_WRITE_TO_HANDLE     = 040h ; Write to File Handle
DOS_DELETE_FILE         = 041h ; Delete a file
DOS_MOVE_FILE_POINTER   = 042h ; Move the file pointer
DOS_GET_SET_ATTRIBUTES  = 043h ; Get/Set File Attributes
DOS_IOCTL               = 044h ; Device-driver control
DOS_DUPLICATE_HANDLE    = 045h ; Duplicate file handle
DOS_FORCE_DUP_HANDLE    = 046h ; Force duplicate file handles
DOS_GET_DIRECTORY       = 047h ; Get the current directory
DOS_ALLOCATE_MEMORY     = 048h ; Allocate memory blocks
DOS_FREE_MEMORY         = 049h ; Release memory blocks
DOS_MODIFY_MEMORY       = 04Ah ; Modify a memory block
DOS_EXEC                = 04Bh ; Execute a program
DOS_TERMINATE_EXE       = 04Ch ; Terminate program
DOS_GET_RETURN_CODE     = 04Dh ; Get DOS return code
DOS_FIND_FIRST          = 04Eh ; Find first directory entry
DOS_FIND_NEXT           = 04Fh ; Find next directory entry
DOS_GET_VERIFY_FLAG     = 054h ; Get the value of DOS's verify flag
DOS_RENAME_FILE         = 056h ; Rename a file
DOS_GET_SET_DATE_TIME   = 057h ; Read or Modify the time and date of a file
DOS_GET_SET_ALLOCATION  = 058h ; Get or set DOS's memory allocation strategy
DOS_GET_EXTENDED_ERRORS = 059h ; Get more detailed info. about a DOS error
DOS_CREATE_TEMP_FILE    = 05Ah ; Create a temporary file
DOS_CREATE_NEW_FILE     = 05Bh ; Create a new file
DOS_CONTROL_ACCESS      = 05Ch ; Set access ability to a region in a file

DOS_NET_HARDWARE        = 05Eh ; Microsoft Network hardware info.

NET_GET_MACHINE_NAME    = 000h ; Get the name of the local machine
NET_SET_PRINTER_SETUP   = 002h ; Set the printer's setup
NET_GET_PRINTER_SETUP   = 003h ; Get the printer's setup

DOS_NET_SYSTEM          = 05Fh ; Microsoft Network system info.

NET_GET_REDIRECTION_LIST    = 002h ; Inspect the system redirection list
NET_REDIRECT_DEVICE         = 003h ; Redirect a device
NET_CANCEL_REDIRECT         = 004h ; Cancel the redirection of a device

DOS_GET_PSP             = 062h ; Get Program Segment Prefix(PSP)
DOS_GET_LEAD_BYTE_TABLE = 063h ; Get the address of the system table
