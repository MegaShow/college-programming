        data    segment
string  db      "MegaShow", "$"
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
        mov     cx, count
        cld
.loop:  lodsb
        cmp     al, 'a'
        jl      .1
        cmp     al, 'z'
        jg      .1
        and     al, 0dfh
.1:     stosb
        loop    .loop
        mov     ah, 02h
        mov     dl, 0ah
        int     21h
        mov     dl, 0dh
        int     21h
        lea     dx, string
        mov     ah, 09h
        int     21h
        mov     ah, 4ch
        int     21h
        code    ends
        end     main
