global inb
global inw
global outb
global outw

; IN: word port
; OUT: byte value
inb:
    push ebp
    mov ebp, esp
        
    mov dx, word [ebp+8]
    in al, dx
    
    mov esp, ebp
    pop ebp
    ret

; IN: word port
; OUT: byte value
inw:    
    push ebp
    mov ebp, esp
        
    mov dx, word [ebp+8]
    in ax, dx
    
    mov esp, ebp
    pop ebp
    ret
    
; IN: word port, byte value
outb:
    push ebp
    mov ebp, esp
        
    mov dx, word [ebp+8]
    mov al, byte [ebp+12]
    out dx, al
    
    mov esp, ebp
    pop ebp
    ret
    
; IN: edi port, esi data
outw:
    push ebp
    mov ebp, esp
        
    mov dx, word [ebp+8]
    mov ax, word [ebp+16]
    out dx, ax
    
    mov esp, ebp
    pop ebp
    ret
