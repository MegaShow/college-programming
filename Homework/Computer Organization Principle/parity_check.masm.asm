        data    segment
string  db      "MegaShow", 0ah, 0dh, "$"
count   equ     $ - string - 1
        data    ends

        code    segment
        assume  cs: code, ds: data, es: data
main:   mov     ax, data
        mov     ds, ax
        mov     es, ax
        lea     dx, string
        lea     di, string
        lea     si, string
        mov     ah, 09h
        int     21h
        cld
        mov     cx, count
        call    printb
        lea     si, string
        mov     cx, count
trans:  lodsb
        test    al, 0ffh
        jnp     .tend
        or      al, 080h
.tend:  stosb
        loop    trans
        lea     si, string
        mov     cx, count
        call    printb
        mov     ah, 4ch
        int     21h

; printb
; @param: si => string address
; @param: cx => length of string
; @reserve: ax, bl, dx
printb: mov     ah, 02h
        lodsb
        mov     bl, al
        mov     dl, al
        int     21h
        mov     dl, ':'
        int     21h
        mov     dh, 80h
.pbloop:test    dh, bl
        mov     dl, '0'
        jz      .pb_0
        inc     dl
.pb_0:  int     21h
        shr     dh, 1
        jnz     .pbloop
        mov     dl, 0ah
        int     21h
        mov     dl, 0dh
        int     21h
        loop    printb
        ret

        code    ends
        end     main
