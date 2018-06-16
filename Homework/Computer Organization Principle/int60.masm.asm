        data    segment
str0    db      "MegaShow", 0ah, 0dh, "12345678", 0ah, 0dh, "$"
        data    ends

        stack0  segment stack
        db      1024 dup(?)
        stack0  ends

        code    segment
        assume  cs: code, ds: data

main:   call    addInt60hUsingInt
        mov     ax, data
        mov     ds, ax
        lea     dx, str0
        int     60h
        mov     ah, 4ch
        int     21h

; addInt60h
addInt60h:
        push    ax
        push    es
        push    di
        xor     ax, ax
        mov     es, ax
        mov     di, 4 * 60h
        cld
        mov     ax, offset int60h
        stosw
        mov     ax, seg int60h
        stosw
        pop     di
        pop     es
        pop     ax
        ret

; addInt60hUsingInt
addInt60hUsingInt:
        push    ax
        push    dx
        push    ds
        mov     ax, seg int60h
        mov     ds, ax
        mov     dx, offset int60h
        mov     ah, 25h
        mov     al, 60h
        int     21h
        pop     ds
        pop     dx
        pop     ax
        ret

; int60h
; @port: 60h
; @input: ds:dx => string address
int60h: push    ax
        mov     ah, 09h
        int     21h
        pop     ax
        iret

        code    ends
        end
