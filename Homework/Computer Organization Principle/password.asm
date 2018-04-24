# by MegaShow
        .data
msg1:   .asciiz "The number of digit is "
msg2:   .asciiz "\nThe number of alpha is "
msg3:   .asciiz "\nThe length of string is "
msg4:   .asciiz "Password Right!\n"
msg5:   .asciiz "Password Error!\n"
str1:   .space  256
str2:   .space  256

        .text
        .globl main
main:   li      $s0, 0          # length of string
        li      $s1, 0          # number of digit
        li      $s2, 0          # number of alpha
        la      $s3, str1       # pointer to char
        
        # input string
        li      $v0, 8
        la      $a0, str1
        li      $a1, 255
        syscall

TransW: lbu     $a2, 0($s3)     # char
        beq     $a2, $zero, TransE
        li      $t0, ' '
        beq     $a2, $t0, .1

        li      $a0, '0'
        li      $a1, '9'
        jal     Include
        add     $s1, $s1, $v0
        li      $a0, 'a'
        li      $a1, 'z'
        jal     Include
        add     $s2, $s2, $v0
        li      $a0, 'A'
        li      $a1, 'Z'
        jal     Include
        add     $s2, $s2, $v0

        la      $t0, str1
        add     $t0, $s0, $t0
        sb      $a2, 0($t0)
        addi    $s0, $s0, 1
.1:     addi    $s3, $s3, 1
        j       TransW

TransE: addi    $s0, $s0, -1

        la      $a0, msg1
        move    $a1, $s1
        jal     PrintStrNum
        la      $a0, msg2
        move    $a1, $s2
        jal     PrintStrNum
        la      $a0, msg3
        move    $a1, $s0
        jal     PrintStrNum

        li      $v0, 11
        la      $t0, str1
        add     $t1, $t0, $s0
        addi    $t1, $t1, 1
ReW:    addi    $t1, $t1, -1
        lbu     $a0, 0($t1)
        syscall
        bne     $t0, $t1, ReW
        li      $a0, '\n'
        syscall

        # input string
        li      $v0, 8
        la      $a0, str2
        li      $a1, 255
        syscall

        li      $t0, 0
        la      $t1, str1
        la      $t2, str2
TravW:  beq     $t0, $s0, Right
        lbu     $t3, 0($t1)
        lbu     $t4, 0($t2)
        bne     $t3, $t4, Error
        addi    $t0, $t0, 1
        addi    $t1, $t1, 1
        addi    $t2, $t2, 1
        j       TravW

Right:  li      $v0, 4
        la      $a0, msg4
        syscall
        j       Exit

Error:  li      $v0, 4
        la      $a0, msg5
        syscall

Exit:   li      $v0, 10
        syscall

# function: Include
# parameter:
#       $a0 => lower limit
#       $a1 => upper limit
#       $a2 => char
# return:
#       $v0 => $a2 in [$a0, $a1] ? 1 : 0
Include:sltu    $t0, $a2, $a0
        sltu    $t1, $a1, $a2
        or      $t0, $t0, $t1
        beq     $t0, $zero, .in
        li      $v0, 0
        jr      $ra
.in:    li      $v0, 1
        jr      $ra

# function: PrintStrNum
# parameter:
#       $a0 => string address
#       $a1 => integer
PrintStrNum:
        li      $v0, 4
        syscall
        li      $v0, 1
        move    $a0, $a1
        syscall
        jr      $ra
