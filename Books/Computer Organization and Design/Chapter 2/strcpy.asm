#
# void strcpy(char x[], char y[]) {
#   int i = 0;
#   while ((x[i] = y[i]) != '\0') {
#     i++;
#   }
# }

strcpy:
  addi $sp, $sp, -4
  sw   $s0, 0($sp)
  add  $s0, $zero, $zero
L1:
  add  $t1, $s0, $a1
  lbu  $t2, 0($t1)
  add  $t1, $s0, $a0
  sb   $t2, 0($t1)
  beq  $t2, $zero, L2
  addi $s0, $s0, 1
  j    L1
L2:
  lw   $s0, 0($sp)
  addi $sp, $sp, 4
  jr   $ra
  nop
