#
# int sum(int n, int acc) {
#   if (n > 0) return sum(n - 1, acc + n);
#   return acc;
# }

# $a0 = n, $a1 = acc
sum:
  slti $t0, $a0, 1 # if n <= 0
  bne  $t0, $zero, sum_exit
  add  $a1, $a1, $a0
  addi $a0, $a0, -1
  j    sum
sum_exit:
  add  $v0, $a1, $zero
  jr   $ra
  nop
