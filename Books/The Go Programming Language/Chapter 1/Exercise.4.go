// 练习 1.4： 修改dup2，出现重复的行时打印文件名称。
package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	counts := make(map[string]int)
	names := make(map[string][]string)
	files := os.Args[1:]
	if len(files) == 0 {
		countLines(os.Stdin, "", counts, nil)
	} else {
		for _, arg := range files {
			f, err := os.Open(arg)
			if err != nil {
				fmt.Fprintf(os.Stderr, "dup: %v\n", err)
				continue
			}
			countLines(f, arg, counts, names)
			f.Close()
		}
	}
	for line, n := range counts {
		if n > 1 {
			var sep rune
			for _, filename := range names[line] {
				fmt.Printf("%c%s", sep, filename)
				sep = ' '
			}
			fmt.Printf(":\n%d\t%s\n", n, line)
		}
	}
}

func countLines(f *os.File, filename string, counts map[string]int, names map[string][]string) {
	input := bufio.NewScanner(f)
	for input.Scan() {
		counts[input.Text()]++
		if len(filename) != 0 {
			names[input.Text()] = append(names[input.Text()], filename)
		}
	}
	// NOTE: ignoring potential errors from input.Err()
}
