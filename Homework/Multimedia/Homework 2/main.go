package main

import "fmt"

func main() {
	test("data/动物卡通图片.jpg", "dist/动物卡通图片")
	test("data/动物照片.jpg", "dist/动物照片")
}

func test(input, output string) {
	fmt.Println("Test data:", input)
	src := ReadFromJpeg(input)
	bytes, f := EncodeJpeg(src)
	Write(output + ".bin", bytes)
	jpeg := DecodeJpeg(f, src.Bounds().Dx(), src.Bounds().Dy())
	WriteToJpeg(output + ".jpg", jpeg)
	gif := EncodeGif(src)
	writeToGif(output + ".gif", gif)
	fmt.Println("JPEG MSE:", GetMeanSquareError(src, jpeg))
	fmt.Println("GIF MSE:", GetMeanSquareError(src, gif.Image[0]))
	fmt.Println()
}
