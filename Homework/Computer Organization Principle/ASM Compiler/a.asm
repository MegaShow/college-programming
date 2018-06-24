addi    $1, $0, 8
ori     $2, $0, 2
or      $3, $2, $1
sub     $4, $3, $1
and     $5, $4, $2
sll     $5, $5, 2
beq     $5, $1, -2
jal     0x0000040
slt     $8, $12, $1
addi    $13, $0, -2
slt     $9, $8, $13
sltiu   $10, $9, 2
sltiu   $11, $10, 0
addi    $13, $13, 1
bltz    $13, -2
j       0x000004C
sw      $2, 4($1)
lw      $12, 4($1)
jr      $31
halt
