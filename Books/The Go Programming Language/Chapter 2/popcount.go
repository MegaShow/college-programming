package main

import (
	"fmt"
)

var pc [256]byte = func() (pc [256]byte) {
	for i, _ := range pc {
		pc[i] = pc[i/2] + byte(i&1)
	}
	return
}()

// 	func init() {
//		for i, _ := range pc {
//	 		pc[i] = pc[i/2] + byte(i&1)
//		}
// 	}

func popCount(x uint64) int {
	return int(pc[byte(x>>(0*8))] +
		pc[byte(x>>(1*8))] +
		pc[byte(x>>(2*8))] +
		pc[byte(x>>(3*8))] +
		pc[byte(x>>(4*8))] +
		pc[byte(x>>(5*8))] +
		pc[byte(x>>(6*8))] +
		pc[byte(x>>(7*8))])
}

func main() {
	fmt.Printf("%d", popCount(126))
}
