section .text
    org     0100h

    mov     ax, cs
    mov     ds, ax
    mov     es, ax
    call    puts
    int     20h         ; 结束程序，等同于21h:00h

puts:
    mov     ah, 09h
    mov     dx, msg
    int     21h         ; 打印字符串，以$结尾
    ret

putsk:
    mov     ax, msg
    mov     bp, ax
    mov     cx, 34d
    mov     ax, 1301h
    mov     bx, 000ch
    mov     dl, 0
    int     10h         ; 显示中断
    ret

section .data
msg:
    db "Hello World!", 0x0a, 0x0d ; len 14
    db "MegaShow", 0x0a, 0x0d ; len 10
    db "12345678", 0x0a, 0x0d ; len 10
    db "$"
