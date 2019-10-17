;***************************************************************
;* Show87 - (C) Copyright 1988, 1989 by Borland International  *
;* VIDEO1.INC - Include module for Show87                      *
;***************************************************************
;
;=============================================================================
; Low Level Video Routines
;
; These are routines to display text and control the screen. All code is BIOS
; compatible. All registers are preserved except those used to return
; parameters. All parameters are passed through registers. VIDEO_INIT must be
; called before the other routines. It is assumed that DS = ES = CS.

;================================================
; Global data.

Video_Mode      db ?         ;present mode
Video_Page      db ?         ;active page
Video_Cols      db ?         ;screen columns

;================================================
; Execute the video interrupt 10H. Preserves the
; extraneous registers not explicitly preserved
; by the interrupt.
;
; Passes all registers back and forth
; tranparently, except for DI, SI, and BP.
;==================================================
;
Video_Int10 proc near
        push    di
        push    si
        push    bp
        int     10h                     ;call video
        pop     bp
        pop     si
        pop     di
        ret
 endp           ;Video_Int10

;================================================
; Initialize the video parameters.
;================================================
;
Video_Init proc near
         push   ax
         push   bx
         mov    ah, 15                  ;function
         call   Video_Int10             ;interrupt 10H
         mov    Video_Mode, al          ;save mode
         mov    Video_Cols, ah          ;save columns
         mov    Video_Page, bh          ;save page
         pop    bx
         pop    ax
         ret
 endp           ;Video_Init

;================================================
; Read the cursor position.
;
; Out: DH= row; DL= column.
;=================================================
;
Video_Cget proc near
         push   ax
         push   bx
         push   cx
         mov    ah, 3                   ;function
         mov    bh, Video_Page          ;page
         call   Video_Int10             ;interrupt 10H
         pop    cx
         pop    bx
         pop    ax
         ret
 endp           ;Video_Cget

;================================================
; Set the cursor position.
;
; In: DH= row; DL= column.
;=================================================
;

Video_Cset proc near
         push   ax
         push   bx
         mov    ah, 2                   ;function
         mov    bh, Video_Page          ;page
         call   Video_Int10             ;interrupt 10H
         pop    bx
         pop    ax
         ret
 endp           ;Video_Cset

;================================================
; Advance the cursor some number of columns. Does
; NOT wrap around. When the last column is
; reached, the cursor is not moved any further.
;
; In: CL= columns to advance.

Video_Cadv proc near
         push   ax
         push   cx
         push   dx

         call   Video_Cget              ;get cursor location
         mov    al, Video_Cols          ;get the screen columns
         dec    al                      ;last screen column
         cmp    al, dl                  ;check if at end
         jae    Vidcad1
         sub    al, dl                  ;get available columns for move
         cmp    cl, al                  ;check if past end
         jbe    Vidcad2
         mov    cl, al                  ;set to maximum

Vidcad1 :
         add    dl, cl                  ;new column
         call   Video_Cset              ;move to new location

Vidcad2 :
         pop    dx
         pop    cx
         pop    ax
         ret
 endp           ;Video_Cadv

;================================================
; Write multiple characters with an attribute to
; the present cursor location.
;
; In: al= character; BL= attribute; CX= count.
;=================================================
;
Video_Wchrs proc near
         or     cx, cx                  ;check if none
         jz     Vidwch1

         push   ax
         push   bx
         mov    ah, 9                   ;function
         mov    bh, Video_Page          ;page
         call   Video_Int10             ;interrupt 10H
         call   Video_Cadv              ;advance cursor
         pop    bx
         pop    ax

Vidwch1  :
        ret
 endp           ;Video_Wchrs

;================================================
; Write a single character and attribute to the
; present cursor location.
;
; In: AL= character; BL= attribute.
;=================================================
Video_Wchr proc near
         push   cx
         mov    cx, 1                   ;count
         call   Video_Wchrs             ;write character
         pop    cx
         ret
 endp           ;Video_Wchr

;================================================
; Scroll a portion of the screen up.
;
; In: DH= upper left hand row; DL= upper left
; hand column; CH= lower left hand row; cl= lower
; left hand column; AL= lines to scroll (0 means
; clear instead of scroll); BL= attribute to use.
;=================================================
;
Video_Spag proc near
         push   ax
         mov    ah, 6                   ;function
         call   Video_Int10             ;interrupt 10H
         pop    ax
         ret
 endp           ;Video_Spag

;================================================
; Clear a portion of the screen.
;
; In: DH= upper left hand row; DL= upper left
; hand column; CH= lower left hand row; cl= lower
; left hand column; BL= attribute to use.
;================================================
;
Video_Cpag proc near
         push   ax
         sub    al, al                  ;scroll lines zero
         call   Video_Spag              ;clear screen
         pop    ax
         ret
 endp           ;Video_Cpag
