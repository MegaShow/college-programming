        data    segment
src     db      "Chen Xiujia", 0ah, 0dh, "16340040", 0ah, 0dh, "$", 0
dest    db      30     dup(0)
        data    ends

        stack   segment stack
        db      16    dup(0)
        stack   ends

        code    segment
        assume  cs: code, ds: data, es: data, ss:stack
main:   mov     ax, data
        mov     ds, ax
        mov     es, ax
        mov     ax, stack
        mov     ss, ax
        lea     di, dest
        lea     si, src
        mov     ax, 25d
        call    strcpy
        mov     si, di
        call    puts
        mov     ah, 4ch
        int     21h

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

        code    ends

        end     main
