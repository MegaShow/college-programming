// echo.go
package main

import (
	"fmt"
	"os"
	"strings"
)

func main() {
	echo4()
}

func echo4() {
	fmt.Println("Echo4:", os.Args[1:])
}

func echo3() {
	fmt.Println("Echo3:", strings.Join(os.Args[1:], " "))
}

func echo2() {
	s, sep := "", ""
	for _, arg := range os.Args[1:] {
		s += sep + arg
		sep = " "
	}
	fmt.Println("Echo2:", s)
}

func echo1() {
	var s, sep string
	for i := 1; i < len(os.Args); i++ {
		s += sep + os.Args[i]
		sep = " "
	}
	fmt.Println("Echo1:", s)
}
