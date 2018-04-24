        org     100h

        section .data
src:    db      "Chen Xiujia", 0ah, 0dh, "16340040", 0ah, 0dh, "$", 0
dest:   times   100     db      0

        section .text
main:   mov     ax, cs
        mov     ds, ax
        mov     es, ax
        mov     di, dest
        mov     si, src
        mov     ax, 25d
        call    strcpy
        mov     si, di
        call    puts
        int     20h

; strcpy
; @param: [di] => dest*
; @param: [si] => src*
; @param: ax   => length
strcpy: mov     bx, di
        mov     dx, si
        mov     cx, ax
        cld
        rep     movsb
        mov     di, bx
        mov     si, dx
        ret

; puts
; @param: [si] => str
puts:   mov     dx, si
        mov     ah, 09h
        int     21h
        ret
