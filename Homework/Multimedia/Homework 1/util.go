package main

import (
	"fmt"
	"image"
	"image/gif"
	"image/jpeg"
	"os"
)

func readFromJpeg(filename string) image.Image {
	f, err := os.Open(filename)
	if err != nil {
		fmt.Fprintf(os.Stderr, err.Error())
		os.Exit(2)
	}
	defer f.Close()
	img, err := jpeg.Decode(f)
	if err != nil {
		fmt.Fprintf(os.Stderr, err.Error())
		os.Exit(2)
	}
	return img
}

func writeToJpeg(filename string, img image.Image) {
	f, err := os.Create(filename)
	if err != nil {
		fmt.Fprintf(os.Stderr, err.Error())
		os.Exit(2)
	}
	defer f.Close()
	jpeg.Encode(f, img, &jpeg.Options{Quality: 100})
}

func writeToGif(filename string, img *gif.GIF) {
	f, err := os.Create(filename)
	if err != nil {
		fmt.Fprintf(os.Stderr, err.Error())
		os.Exit(2)
	}
	defer f.Close()
	err = gif.EncodeAll(f, img)
	if err != nil {
		fmt.Fprintf(os.Stderr, err.Error())
		os.Exit(2)
	}
}
