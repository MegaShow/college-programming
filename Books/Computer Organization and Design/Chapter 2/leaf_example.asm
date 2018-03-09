#
# def leaf_example($a0, $a1, $a2, $a3)
#  return ($a0 + $a1) - ($a2 - $a3)
# end

leaf_example:
  # 分配3个空间储存寄存器旧值
  addi $sp, $sp, -12
  sw   $t1, 8($sp)
  sw   $t0, 4($sp)
  sw   $s0, 0($sp)
  # 函数体
  add  $t0, $a0, $a1
  add  $t1, $a2, $a3
  sub  $s0, $t0, $t1
  add  $v0, $s0, $zero
  # 恢复寄存器旧值
  lw   $s0, 0($sp)
  lw   $t0, 4($sp)
  lw   $t1, 8($sp)
  addi $sp, $sp, 12
  jr   $ra
  nop
