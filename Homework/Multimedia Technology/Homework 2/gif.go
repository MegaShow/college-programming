package main

import (
	"github.com/andybons/gogif"
	"image"
	"image/gif"
)

func EncodeGif(img image.Image) gif.GIF {
	var gifImg gif.GIF
	palettedImg := image.NewPaletted(img.Bounds(), nil)
	quantizer := gogif.MedianCutQuantizer{NumColor: 256}
	quantizer.Quantize(palettedImg, img.Bounds(), img, image.ZP)
	gifImg.Image = []*image.Paletted{palettedImg}
	gifImg.Delay = []int{0}
	return gifImg
}
