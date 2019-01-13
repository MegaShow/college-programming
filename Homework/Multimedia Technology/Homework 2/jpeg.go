package main

import (
	"fmt"
	"image"
)

func EncodeJpeg(img image.Image) ([]byte, [][]YUVDCT) {
	fmt.Print("Encode: RGB -> YUV")
	ycbcr := GetYUVArray(img)
	fmt.Print(" -> Resample")
	Resample(ycbcr)
	Size(&ycbcr)
	fmt.Print(" -> DCT")
	f := GetDCT(ycbcr)
	fmt.Print(" -> Quantify")
	Quantify(f)
	fmt.Println(" -> Entropy")
	bytes := Entropy(f)
	return bytes, f
}

func DecodeJpeg(f [][]YUVDCT, dx, dy int) image.Image {
	fmt.Print("Decode: IQuantify")
	IQuantify(f)
	fmt.Print(" -> IDCT")
	ycbcr := GetIDCT(f)
	Resize(&ycbcr, dx, dy)
	fmt.Println(" -> YUV -> RGB")
	return GetImage(ycbcr)
}
