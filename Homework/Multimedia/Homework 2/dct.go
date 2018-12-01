package main

import (
	"fmt"
	"math"
	"os"
)

type YUVDCT struct {
	Y int
	U int
	V int
}

func (dct *YUVDCT) Set(y, u, v int) {
	dct.Y, dct.U, dct.V = y, u, v
}

func GetDCT(data [][]YUV) (f [][]YUVDCT) {
	if len(data)%8 != 0 || (len(data) != 0 && len(data[0])%8 != 0) {
		fmt.Println("Please resize YUV data")
		os.Exit(2)
	}
	f = make([][]YUVDCT, len(data))
	for u := 0; u < len(data); u++ {
		f[u] = make([]YUVDCT, len(data[u]))
		for v := 0; v < len(data[u]); v++ {
			var dcty, dctu, dctv float64
			for i := 0; i < 8; i++ {
				for j := 0; j < 8; j++ {
					dct := math.Cos(float64((2*i+1)*(u%8))*math.Pi/16) *
						math.Cos(float64((2*j+1)*(v%8))*math.Pi/16)
					dcty += dct * float64(data[u/8*8+i][v/8*8+j].Y)
					dctu += dct * float64(data[u/8*8+i][v/8*8+j].U)
					dctv += dct * float64(data[u/8*8+i][v/8*8+j].V)
				}
			}
			c := constant(u%8) * constant(v%8) / 4
			f[u][v].Set(int(math.Round(c*dcty)), int(math.Round(c*dctu)), int(math.Round(c*dctv)))
		}
	}
	return
}

func GetIDCT(f [][]YUVDCT) (data [][]YUV) {
	data = make([][]YUV, len(f))
	for i := 0; i < len(f); i++ {
		data[i] = make([]YUV, len(f[i]))
		for j := 0; j < len(f[i]); j++ {
			var idcty, idctu, idctv float64
			for u := 0; u < 8; u++ {
				for v := 0; v < 8; v++ {
					idct := constant(u) * constant(v) / 4 *
						math.Cos(float64((2*(i%8)+1)*u)*math.Pi/16) *
						math.Cos(float64((2*(j%8)+1)*v)*math.Pi/16)
					idcty += idct * float64(f[i/8*8+u][j/8*8+v].Y)
					idctu += idct * float64(f[i/8*8+u][j/8*8+v].U)
					idctv += idct * float64(f[i/8*8+u][j/8*8+v].V)
				}
			}
			data[i][j].Set(int32(math.Round(idcty)), int32(math.Round(idctu)), int32(math.Round(idctv)))
		}
	}
	return
}

func constant(a int) float64 {
	if a == 0 {
		return math.Sqrt(2) / 2
	}
	return 1
}
