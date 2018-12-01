package main

import (
	"fmt"
	"image"
	"image/gif"
	"image/jpeg"
	"os"
)

func ReadFromJpeg(filename string) image.Image {
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

func WriteToJpeg(filename string, img image.Image) {
	f, err := os.Create(filename)
	if err != nil {
		fmt.Fprintf(os.Stderr, err.Error())
		os.Exit(2)
	}
	defer f.Close()
	jpeg.Encode(f, img, &jpeg.Options{Quality: 100})
}

func writeToGif(filename string, img gif.GIF) {
	f, err := os.Create(filename)
	if err != nil {
		fmt.Fprintf(os.Stderr, err.Error())
		os.Exit(2)
	}
	defer f.Close()
	err = gif.EncodeAll(f, &img)
	if err != nil {
		fmt.Fprintf(os.Stderr, err.Error())
		os.Exit(2)
	}
}

func Write(filename string, bytes []byte) {
	f, err := os.Create(filename)
	if err != nil {
		fmt.Fprintf(os.Stderr, err.Error())
		os.Exit(2)
	}
	defer f.Close()
	f.Write(bytes)
}

func GetMeanSquareError(src, dst image.Image) float64 {
	var mse float64
	for i := 0; i < src.Bounds().Dx(); i++ {
		for j := 0; j < src.Bounds().Dy(); j++ {
			r1, g1, b1, _ := src.At(i, j).RGBA()
			r2, g2, b2, _ := dst.At(i, j).RGBA()
			r1, g1, b1 = r1 >> 8 & 0xff, g1 >> 8 & 0xff, b1 >> 8 & 0xff
			r2, g2, b2 = r2 >> 8 & 0xff, g2 >> 8 & 0xff, b2 >> 8 & 0xff
			mse += float64((r1-r2)*(r1-r2)+(g1-g2)*(g1-g2)+(b1-b2)*(b1-b2)) / 3
		}
	}
	return mse / float64(src.Bounds().Dx()*src.Bounds().Dy())
}
