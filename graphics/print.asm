global print
global strlen
global clear

CONSOLE_BUFFER equ 0xb8000
ROWS equ 25
COLUMNS equ 160

section .data
    cursorx db 0
    cursory db 0

; input : edi : pointer to string
print:
    xor ecx, ecx
    sub ecx, 1
    
    .loop:
        add ecx, 1
        cmp word [edi+ecx], 0
        
        je print.break
        
        mov eax, [cursorx]
        imul eax, [cursory]
        add eax, ecx ;string offset + string index + cursor position
        ;mov byte [CONSOLE_BUFFER], al
        mov bh, byte [edi+ecx] ;load char from memory
        mov byte [CONSOLE_BUFFER+ecx*2], bh
        
        jmp print.loop
        
    .break:
        ret
    
; 0 = black, f = white
; 0x background color, text color, char
; 0x0f44
clear:
    xor ecx, ecx
    
    .rowloop:
        mov word [CONSOLE_BUFFER+ecx*2], 0x0f00
        inc ecx
        cmp ecx, ROWS * COLUMNS
        jne clear.rowloop
        
    ret
    
; input edi : string location
; output eax : string size
strlen:
    xor ecx, ecx ;zeroing the counter
    dec ecx
    
    .strlenloop:
        inc ecx 
        cmp byte [edi+ecx], 0
        jne strlen.strlenloop
        
    mov eax, ecx
    ret
