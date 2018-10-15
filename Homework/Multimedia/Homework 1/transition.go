package main

import (
	"github.com/andybons/gogif"
	"image"
	"image/color"
	"image/gif"
	"math"
	"strconv"
)

func transition() {
	imgNobel := readFromJpeg("data/诺贝尔.jpg")
	imgLena := readFromJpeg("data/lena.jpg")
	var gifRes, gifRedRes gif.GIF
	originX, originY := imgLena.Bounds().Dx()/2, imgLena.Bounds().Dy()/2
	radius := math.Sqrt(float64(originX*originX + originY*originY))
	for t := 0.0; t <= 1.01; t += 0.05 {
		imgRes := image.NewRGBA(imgLena.Bounds())
		imgRedRes := image.NewRGBA(imgLena.Bounds())
		for x := 0; x < imgLena.Bounds().Dx(); x++ {
			for y := 0; y < imgLena.Bounds().Dy(); y++ {
				distance := math.Sqrt(float64((x-originX)*(x-originX) + (y-originY)*(y-originY)))
				var c color.Color
				if distance <= radius*t {
					c = imgLena.At(x, y)
				} else {
					c = imgNobel.At(x, y)
				}
				imgRes.Set(x, y, c)
				r, _, _, _ := c.RGBA()
				imgRedRes.Set(x, y, color.RGBA{R: uint8(r >> 8 & 0xff), A: 0xff})
			}
		}
		writeToJpeg("dist/transition/frames/"+strconv.FormatFloat(t, 'f', 2, 64)+".jpg", imgRes)
		writeToJpeg("dist/transition/frames/red-"+strconv.FormatFloat(t, 'f', 2, 64)+".jpg", imgRedRes)
		palettedImgRes := image.NewPaletted(imgRes.Bounds(), nil)
		palettedImgRedRes := image.NewPaletted(imgRedRes.Bounds(), nil)
		quantizer := gogif.MedianCutQuantizer{NumColor: 256}
		quantizer.Quantize(palettedImgRes, imgRes.Bounds(), imgRes, image.ZP)
		quantizer.Quantize(palettedImgRedRes, imgRedRes.Bounds(), imgRedRes, image.ZP)
		gifRes.Image = append(gifRes.Image, palettedImgRes)
		gifRes.Delay = append(gifRes.Delay, 0)
		gifRedRes.Image = append(gifRedRes.Image, palettedImgRedRes)
		gifRedRes.Delay = append(gifRedRes.Delay, 0)
	}
	writeToGif("dist/transition/transition.gif", &gifRes)
	writeToGif("dist/transition/red-transition.gif", &gifRedRes)
}
