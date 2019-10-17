.386
.model   flat,stdcall
option   casemap:none

WinMain  proto :DWORD,:DWORD,:DWORD,:DWORD
WndProc  proto :DWORD,:DWORD,:DWORD,:DWORD
Display  proto :DWORD
ConvertString  proto :word
Calculate   proto
include      menuID.INC

include      windows.inc
include      user32.inc
include      kernel32.inc
include      gdi32.inc
include      shell32.inc

includelib   user32.lib
includelib   kernel32.lib
includelib   gdi32.lib
includelib   shell32.lib

Item	struct
	    itemName   		db  10 dup(' ')
	    discount  		dw  0
	    cost     		dw  0
	    price  			dw  0
	    quantity    	dw  0
		sold_num   		dw 	0
		recommend_level dw 	0
Item	ends

.data
ClassName    db       'TryWinClass',0
AppName      db       'Online Shop @author GS',0
MenuName     db       'MyMenu',0
DlgName	     db       'MyDialog',0
AboutMsg     db       'Code by Gesong in Class CS1703',0
hInstance    dd       0
CommandLine  dd       0
buf	    Item <'pen', 10, 35, 56, 70, 25, 0>
		Item  <'book', 9, 12, 30, 25, 5, 0>
		Item  <'bag', 9, 40, 100, 45, 5, 0>
		Item  <'note',5,30,50,30,25, 0>
		Item  <'pen',10,35,56,70,25,0>
		Item  <'pen',10,35,56,70,25,0>
itemNum equ  ($ - buf)/22
msg_name     db       'Name',0
msg_discount  db      'Discount',0
msg_cost     db       'Cost',0
msg_price  db         'Price',0
msg_quantity    db       'Quantity',0
msg_sold_num db			'Sold_num',0
msg_recommend_level db  'Recommend_level', 0

stringBuf 		db 100 dup(0)

menuItem     db       0   ;当前菜单状态, 1=处于list, 0=Clear

.code
Start:	     invoke GetModuleHandle,NULL
	     mov    hInstance,eax
	     invoke GetCommandLine
	     mov    CommandLine,eax
	     invoke WinMain,hInstance,NULL,CommandLine,SW_SHOWDEFAULT
	     invoke ExitProcess,eax
	     ;;
WinMain      proc   hInst:DWORD,hPrevInst:DWORD,CmdLine:DWORD,CmdShow:DWORD
	     LOCAL  wc:WNDCLASSEX
	     LOCAL  msg:MSG
	     LOCAL  hWnd:HWND
             invoke RtlZeroMemory,addr wc,sizeof wc
	     mov    wc.cbSize,SIZEOF WNDCLASSEX
	     mov    wc.style, CS_HREDRAW or CS_VREDRAW
	     mov    wc.lpfnWndProc, offset WndProc
	     mov    wc.cbClsExtra,NULL
	     mov    wc.cbWndExtra,NULL
	     push   hInst
	     pop    wc.hInstance
	     mov    wc.hbrBackground,COLOR_WINDOW+1
	     mov    wc.lpszMenuName, offset MenuName
	     mov    wc.lpszClassName,offset ClassName
	     invoke LoadIcon,NULL,IDI_APPLICATION
	     mov    wc.hIcon,eax
	     mov    wc.hIconSm,0
	     invoke LoadCursor,NULL,IDC_ARROW
	     mov    wc.hCursor,eax
	     invoke RegisterClassEx, addr wc
	     INVOKE CreateWindowEx,NULL,addr ClassName,addr AppName,\
                    WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,\
                    CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,\
                    hInst,NULL
	     mov    hWnd,eax
	     INVOKE ShowWindow,hWnd,SW_SHOWNORMAL
	     INVOKE UpdateWindow,hWnd
	     ;;
MsgLoop:     INVOKE GetMessage,addr msg,NULL,0,0
             cmp    EAX,0
             je     ExitLoop
             INVOKE TranslateMessage,addr msg
             INVOKE DispatchMessage,addr msg
	     jmp    MsgLoop 
ExitLoop:    mov    eax,msg.wParam
	     ret
WinMain      endp

WndProc      proc   hWnd:DWORD,uMsg:DWORD,wParam:DWORD,lParam:DWORD
	     LOCAL  hdc:HDC
	     LOCAL  ps:PAINTSTRUCT
     .IF     uMsg == WM_DESTROY
	     invoke PostQuitMessage,NULL
     .ELSEIF uMsg == WM_KEYDOWN
	    .IF     wParam == VK_F1
             ;;your code
	    .ENDIF
     .ELSEIF uMsg == WM_COMMAND
	    .IF     wParam == IDM_FILE_EXIT
		    invoke SendMessage,hWnd,WM_CLOSE,0,0
	    .ELSEIF wParam == IDM_FILE_CLEAR
		    mov menuItem, 0
		    invoke InvalidateRect,hWnd,0,1  ;���������ͻ���
		    invoke UpdateWindow, hWnd
		.ELSEIF wParam == IDM_ACTION_RECOMMENDATION ; 计算推荐度
			mov menuItem, 2
			invoke Calculate
		    invoke InvalidateRect,hWnd,0,1  
		    invoke UpdateWindow, hWnd
		.ELSEIF wParam == IDM_ACTION_LIST ; 显示所有商品
			mov menuItem, 3
		    invoke InvalidateRect,hWnd,0,1  
		    invoke UpdateWindow, hWnd
	    .ELSEIF wParam == IDM_HELP_ABOUT
		    invoke MessageBox,hWnd,addr AboutMsg,addr AppName,0
		
	    .ENDIF
     .ELSEIF uMsg == WM_PAINT
             invoke BeginPaint,hWnd, addr ps
             mov hdc,eax
	     .IF menuItem == 1
		 invoke Display,hdc
		 .ELSEIF menuItem == 2
		 invoke Display, hdc
		 .ELSEIF menuItem == 3
		 invoke Display, hdc
	     .ENDIF
	     invoke EndPaint,hWnd,addr ps
     .ELSE
             invoke DefWindowProc,hWnd,uMsg,wParam,lParam
             ret
     .ENDIF
  	     xor    eax,eax
	     ret
WndProc      endp

Display	proc   hdc:HDC
		LOCAL lineheight:dword
		LOCAL currentItem:dword

		mov lineheight, 10
		mov currentItem, 0

        invoke TextOut,hdc,10 ,lineheight,offset msg_name,4
        invoke TextOut,hdc,110,lineheight,offset msg_discount,8
        invoke TextOut,hdc,210,lineheight,offset msg_cost,4
        invoke TextOut,hdc,310,lineheight,offset msg_price,5
        invoke TextOut,hdc,410,lineheight,offset msg_quantity,8
		invoke TextOut,hdc,510,lineheight,offset msg_sold_num,8
		invoke TextOut,hdc,610,lineheight,offset msg_recommend_level,15

loopa:
		add lineheight, 30
		mov edx, currentItem
		invoke TextOut, hdc, 10, lineheight, addr buf[edx].itemName, 10

		mov edx, currentItem
		invoke ConvertString, buf[edx].discount
		invoke TextOut, hdc, 110, lineheight, addr stringBuf, 5

		mov edx, currentItem
		invoke ConvertString, buf[edx].cost
		invoke TextOut, hdc, 210, lineheight, addr stringBuf, 5

		mov edx, currentItem
		invoke ConvertString, buf[edx].price
		invoke TextOut, hdc, 310, lineheight, addr stringBuf, 5

		mov edx, currentItem
		invoke ConvertString, buf[edx].quantity
		invoke TextOut, hdc, 410, lineheight, addr stringBuf, 5

		mov edx, currentItem
		invoke ConvertString, buf[edx].sold_num
		invoke TextOut, hdc, 510, lineheight, addr stringBuf, 5

		mov edx, currentItem
		invoke ConvertString, buf[edx].recommend_level
		invoke TextOut, hdc, 610, lineheight, addr stringBuf, 5


		add currentItem, 22
		cmp currentItem, itemNum * 22
		jne loopa
			 
        ret
Display endp

ConvertString proc num:word
    pusha
    mov     ax, num
    mov     esi, offset stringBuf
    mov     ebx, 0
clear_buf:
    mov     byte ptr[esi+ebx], ' '
    inc     ebx
    cmp     ebx, 100
    jne     clear_buf
    mov     bx, 10
    mov     cx, 0
loopm:
    mov     dx, 0
    div     bx
    add     dl, '0'
    push    dx
    inc     cx
    cmp     ax, 0
    jne     loopm
loopn:
    pop     dx
    mov     byte ptr[esi], dl
    inc     esi
    dec     cx
    cmp     cx, 0
    jne     loopn
    popa
    ret
ConvertString endp

Calculate proc
    pushad

	mov ebx, 0
loopc:
    mov ax, buf[ebx].price
    mov dl, byte ptr buf[ebx].discount
    mov dh, 0
    ; 销售价*折扣
    mul dx
    mov cx, 10
    ; 除以 10
    div cx
    ; 结果放在 cx
    mov cx, ax
    mov ax, buf[ebx].cost
    mov dx, 128
    mul dx
    mov dx, 0
    div cx

    mov cx, ax
    mov ax, word ptr buf[ebx].sold_num
    mov dx, 128
    mul dx
    mov dx, 0
    div word ptr buf[ebx].quantity
    add ax, cx

    mov word ptr buf[bx].recommend_level, ax
	add ebx, 22
	cmp ebx, itemNum * 22
	jne loopc
    popad
    ret
Calculate endp
    end  Start
