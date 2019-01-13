        data    segment
inputa          db      "Input number a: ", "$"
inputb          db      "Input number b: ", "$"
err             db      "Input invalid", 0ah, 0dh, "$"
div0err         db      "Div 0 error", 0ah, 0dh, "$"
print_a_plus_b  db      "a + b", 0ah, 0dh, "$"
print_a_sub_b   db      "a - b", 0ah, 0dh, "$"
print_a_mul_b   db      "a * b", 0ah, 0dh, "$"
print_a_div_b   db      "a / b", 0ah, 0dh, "$"
print_a_mod_b   db      "a % b", 0ah, 0dh, "$"
str_bin         db      "  bin: 0b$"
str_dec         db      "  dec: $"
str_hex         db      "  hex: 0x$"
stra            db      16, ?, 16 dup(?)
strb            db      16, ?, 16 dup(?)
vara            dw      0ffffh
varb            dw      0ffffh
        data    ends

        stacks  segment stack
        db      1024 dup(?)
        stacks  ends

        code    segment
        assume  cs: code, ds: data, ss: stacks
main:   mov     ax, data
        mov     ds, ax
        mov     ax, stacks
        mov     ss, ax

        lea     dx, vara
        push    dx
        lea     dx, stra
        push    dx
        lea     dx, inputa
        push    dx
        call    input

        lea     dx, varb
        push    dx
        lea     dx, strb
        push    dx
        lea     dx, inputb
        push    dx
        call    input

        mov     ax, vara
        add     ax, varb
        lea     dx, print_a_plus_b
        push    ax
        push    dx
        call    print

        mov     ax, vara
        sub     ax, varb
        lea     dx, print_a_sub_b
        push    ax
        push    dx
        call    print

        mov     ax, vara
        mul     varb
        lea     dx, print_a_mul_b
        push    ax
        push    dx
        call    print

        cmp     varb, 0
        je      .jmp2div0error
        mov     ax, vara
        xor     dx, dx
        div     varb
        mov     bx, dx
        lea     dx, print_a_div_b
        push    ax
        push    dx
        call    print
        lea     dx, print_a_mod_b
        push    bx
        push    dx
        call    print

        mov     ah, 4ch
        int     21h

.jmp2div0error:
        call    div0error

; input
; @param: [word] address => output string
; @param: [word] address => input string
; @param: [word] address => store value
input:  push    ax
        push    bx
        push    dx
        push    si
        push    bp
        mov     bp, sp
        mov     dx, [bp + 12]
        mov     ah, 09h
        int     21h
        mov     dx, [bp + 14]
        mov     ah, 0ah
        int     21h
        mov     dl, 0ah
        mov     ah, 02h
        int     21h
        mov     si, [bp + 14]
        add     si, 2
        xor     dx, dx
        xor     bx, bx
.loop:  lodsb
        cmp     al, '0'
        jl      .1
        cmp     al, '9'
        jg      .1
        sub     al, '0'
        xor     ah, ah
        xchg    ax, bx
        mov     dx, 10
        mul     dx
        add     bx, ax
        jmp     .loop
.1:     cmp     al, 0dh
        jne     error
        mov     si, [bp + 16]
        mov     [si], bx
        pop     bp
        pop     si
        pop     dx
        pop     bx
        pop     ax
        ret     6

; print
; @param: [word] address => output string
; @param: [word] value => print value
print:  push    ax
        push    bx
        push    cx
        push    dx
        push    bp
        mov     bp, sp
        mov     dx, [bp + 12]
        mov     ah, 09h
        int     21h
        mov     bx, 2
        lea     dx, str_bin
        jmp     .tox
.to10:  mov     bx, 10
        lea     dx, str_dec
        jmp     .tox
.to16:  mov     bx, 16
        lea     dx, str_hex
.tox:   mov     ah, 09h
        int     21h
        mov     ax, [bp + 14]
        xor     cx, cx
.divx:  xor     dx, dx
        div     bx
        cmp     dx, 0ah
        jl      .num
        add     dx, 'a' - 10 - '0'
.num:   add     dx, '0'
        inc     cx
        push    dx
        cmp     ax, 0
        jne     .divx
.plx:   pop     dx
        mov     ah, 02h
        int     21h
        loop    .plx
        cmp     bl, 2
        je      .to10
        cmp     bl, 10
        je      .to16
        mov     dl, 0ah
        int     21h
        mov     dl, 0dh
        int     21h
        pop     bp
        pop     dx
        pop     cx
        pop     bx
        pop     ax
        ret     4

; error
error:  lea     dx, err
        mov     ah, 09h
        int     21h
        mov     ah, 4ch
        int     21h

; div0error
div0error:
        lea     dx, div0err
        mov     ah, 09h
        int     21h
        mov     ah, 4ch
        int     21h

        code    ends
        end     main
