// 练习 1.3： 做实验测量潜在低效的版本和使用了strings.Join的版本的运行时间差异。
package main

import (
	"fmt"
	"os"
	"strings"
	"time"
)

func main() {
	/* for i := 0; i < 100000; i++ {
		os.Args = append(os.Args, "xyz")
	} */
	start := time.Now()
	echo1()
	fmt.Println(time.Now().Sub(start))
	start = time.Now()
	echo2()
	fmt.Println(time.Now().Sub(start))
	start = time.Now()
	echo3()
	fmt.Println(time.Now().Sub(start))
}

func echo3() {
	strings.Join(os.Args[1:], " ")
}

func echo2() {
	s, sep := "", ""
	for _, arg := range os.Args[1:] {
		s += sep + arg
		sep = " "
	}
}

func echo1() {
	var s, sep string
	for i := 1; i < len(os.Args); i++ {
		s += sep + os.Args[i]
		sep = " "
	}
}
