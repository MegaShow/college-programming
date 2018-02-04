#
# while $s3($s6) == $s5
#   $s3++
#   print "i++\n"
# end

  .data
message:  .asciiz "i++\n"
array:    .word 1, 1, 1, 1, 0, 0, 0
  .text
main:
  # syscall setting
  li      $v0, 4
  la      $a0, message
  # initial
  li      $s3, 0 # i
  li      $s5, 1 # k
  la      $s6, array # save
DO_WHILE:
  sll     $t0, $s3, 2
  add     $t0, $t0, $s6
  lw      $t0, 0($t0)
  bne     $t0, $s5, END_WHILE
  syscall
  addi    $s3, $s3, 1
  j       DO_WHILE
END_WHILE:
  nop
