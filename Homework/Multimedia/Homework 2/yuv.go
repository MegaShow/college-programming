package main

import (
	"image"
	"image/color"
)

type YUV struct {
	Y uint8
	U uint8
	V uint8
}

func (c *YUV) Set(y, u, v int32) {
	c.Y, c.U, c.V = check(y), check(u), check(v)
}

func GetYUVArray(img image.Image) (res [][]YUV) {
	res = make([][]YUV, img.Bounds().Dx())
	for i := 0; i < img.Bounds().Dx(); i++ {
		res[i] = make([]YUV, img.Bounds().Dy())
		for j := 0; j < img.Bounds().Dy(); j++ {
			rr, rg, rb, _ := img.At(i, j).RGBA()
			r, g, b := float64(rr>>8&0xff), float64(rg>>8&0xff), float64(rb>>8&0xff)
			yy := int32(0.299*r) + int32(0.587*g) + int32(0.114*b)
			cb := int32(-0.169*r) - int32(0.331*g) + int32(0.5*b) + 128
			cr := int32(0.5*r) - int32(0.419*g) - int32(0.081*b) + 128
			res[i][j].Set(yy, cb, cr)
		}
	}
	return
}

func GetImage(data [][]YUV) image.Image {
	img := image.NewRGBA(image.Rect(0, 0, len(data), len(data[0])))
	for i := 0; i < len(data); i++ {
		for j := 0; j < len(data[i]); j++ {
			r := check(int32(data[i][j].Y) + int32(1.13983*float64(int32(data[i][j].V)-128)))
			g := check(int32(data[i][j].Y) - int32(0.39465*float64(int32(data[i][j].U)-128)) - int32(0.58060*float64(int32(data[i][j].V)-128)))
			b := check(int32(data[i][j].Y) + int32(2.03211*float64(int32(data[i][j].U)-128)))
			img.Set(i, j, color.RGBA{R: r, G: g, B: b, A: 0xff})
		}
	}
	return img
}

func check(value int32) uint8 {
	if value < 0 {
		value = 0
	} else if value > 255 {
		value = 255
	}
	return uint8(value)
}

func Resample(data [][]YUV) {
	for i := 0; i < len(data); i++ {
		for j := 0; j < len(data[i]); j++ {
			data[i][j].V = data[i-i%2][j-j%2].V
			data[i][j].U = data[i-i%2][j-j%2].U
		}
	}
}

func Size(data *[][]YUV) {
	l := len(*data)
	for i := 0; i < l; i++ {
		if len((*data)[i])%8 != 0 {
			(*data)[i] = append((*data)[i], make([]YUV, 8-len((*data)[i])%8)...)
		}
	}
	if l%8 != 0 {
		*data = append(*data, make([][]YUV, 8-l%8)...)
		for i := l; i < len(*data); i++ {
			(*data)[i] = make([]YUV, len((*data)[0]))
		}
	}
}

func Resize(data *[][]YUV, dx, dy int) {
	for i := 0; i < dx; i++ {
		(*data)[i] = (*data)[i][:dy]
	}
	*data = (*data)[:dx]
}
