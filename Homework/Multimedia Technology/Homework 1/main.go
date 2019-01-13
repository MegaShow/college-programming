package main

import (
	"fmt"
	"os"
	"strings"
)

func main() {
	if len(os.Args) != 2 {
		fmt.Fprintf(os.Stderr, "Too much or fewer parameters.")
		os.Exit(2)
	}
	switch strings.ToLower(os.Args[1]) {
	case "transition":
		transition()
		break
	case "median-cut":
		medianCut()
		break
	}
}
