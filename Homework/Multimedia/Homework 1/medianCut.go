package main

import (
	"image"
	"image/color"
	"sort"
)

func medianCut() {
	img := readFromJpeg("data/redapple.jpg")
	var paletteArray []uint32
	var paletteColorArray []color.Color
	paletteColorMap := make(map[uint32]uint8)
	for x := 0; x < img.Bounds().Dx(); x++ {
		for y := 0; y < img.Bounds().Dy(); y++ {
			r, g, b, a := img.At(x, y).RGBA()
			rgba := a>>8&0xff<<24 + r>>8&0xff<<16 + g>>8&0xff<<8 + b>>8&0xff
			paletteArray = append(paletteArray, rgba)
		}
	}
	setPaletteColor(paletteArray, 0, &paletteColorArray, &paletteColorMap)
	imgRes := image.NewPaletted(img.Bounds(), paletteColorArray)
	for x := 0; x < imgRes.Bounds().Dx(); x++ {
		for y := 0; y < imgRes.Bounds().Dy(); y++ {
			r, g, b, a := img.At(x, y).RGBA()
			rgba := a>>8&0xff<<24 + r>>8&0xff<<16 + g>>8&0xff<<8 + b>>8&0xff
			imgRes.SetColorIndex(x, y, paletteColorMap[rgba])
		}
	}
	writeToJpeg("dist/medianCut/redapple.jpg", imgRes)
}

func setPaletteColor(paletteArray []uint32, depth uint, colorArray *[]color.Color, colorMap *map[uint32]uint8) {
	l := uint32(len(paletteArray))
	if l == 1 || 1<<depth == 256 {
		var rAvg, gAvg, bAvg, aAvg uint32
		for _, v := range paletteArray {
			(*colorMap)[v] = uint8(len(*colorArray))
			aAvg += 0xff & (v >> 24)
			rAvg += 0xff & (v >> 16)
			gAvg += 0xff & (v >> 8)
			bAvg += 0xff & v
		}
		aAvg, rAvg, gAvg, bAvg = aAvg/l, rAvg/l, gAvg/l, bAvg/l
		*colorArray = append(*colorArray, color.RGBA{R: uint8(rAvg), G: uint8(gAvg), B: uint8(bAvg), A: uint8(aAvg)})
		return
	}
	if depth%3 == 0 {
		sort.Slice(paletteArray, func(i, j int) bool { return paletteArray[i]>>16&0xff < paletteArray[j]>>16&0xff })
	} else if depth%3 == 1 {
		sort.Slice(paletteArray, func(i, j int) bool { return paletteArray[i]>>8&0xff < paletteArray[j]>>8&0xff })
	} else {
		sort.Slice(paletteArray, func(i, j int) bool { return paletteArray[i]&0xff < paletteArray[j]&0xff })
	}
	setPaletteColor(paletteArray[:l/2], depth+1, colorArray, colorMap)
	setPaletteColor(paletteArray[l/2:], depth+1, colorArray, colorMap)
}
