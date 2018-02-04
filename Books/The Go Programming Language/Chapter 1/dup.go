// dup.go
package main

import (
	"bufio"
	"fmt"
	"io/ioutil"
	"os"
	"strings"
)

func main() {
	counts := make(map[string]int)
	files := os.Args[1:]
	if len(files) == 0 {
		input := bufio.NewScanner(os.Stdin)
		for input.Scan() {
			counts[input.Text()]++
		}
	} else {
		for _, arg := range files {
			data, err := ioutil.ReadFile(arg)
			if err != nil {
				fmt.Fprintf(os.Stderr, "dup: %v\n", err)
				continue
			}
			for _, line := range strings.Split(string(data), "\n") {
				counts[line]++
			}
		}
	}
	for line, n := range counts {
		if n > 1 {
			fmt.Printf("%d\t%s\n", n, line)
		}
	}
}
