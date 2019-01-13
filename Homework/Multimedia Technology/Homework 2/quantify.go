package main

import "math"

var (
	TableY = [8][8]int{
		{16, 11, 10, 16, 24, 40, 51, 61},
		{12, 12, 14, 19, 26, 58, 60, 55},
		{14, 13, 16, 24, 40, 57, 69, 56},
		{14, 17, 22, 29, 51, 87, 80, 62},
		{18, 22, 37, 56, 68, 109, 103, 77},
		{24, 35, 55, 64, 81, 104, 113, 92},
		{49, 64, 78, 87, 103, 121, 120, 101},
		{72, 92, 95, 98, 112, 100, 103, 99},
	}
	TableC = [8][8]int{
		{17, 18, 24, 47, 99, 99, 99, 99},
		{18, 21, 26, 66, 99, 99, 99, 99},
		{24, 26, 56, 99, 99, 99, 99, 99},
		{47, 66, 99, 99, 99, 99, 99, 99},
		{99, 99, 99, 99, 99, 99, 99, 99},
		{99, 99, 99, 99, 99, 99, 99, 99},
		{99, 99, 99, 99, 99, 99, 99, 99},
		{99, 99, 99, 99, 99, 99, 99, 99},
	}
)

func Quantify(f [][]YUVDCT) {
	for i := 0; i < len(f); i++ {
		for j := 0; j < len(f[i]); j++ {
			y := math.Round(float64(f[i][j].Y) / float64(TableY[j%8][i%8]))
			u := math.Round(float64(f[i][j].U) / float64(TableC[j%8][i%8]))
			v := math.Round(float64(f[i][j].V) / float64(TableC[j%8][i%8]))
			f[i][j].Set(int(y), int(u), int(v))
		}
	}
}

func IQuantify(f [][]YUVDCT) {
	for i := 0; i < len(f); i++ {
		for j := 0; j < len(f[i]); j++ {
			y := math.Round(float64(f[i][j].Y * TableY[j%8][i%8]))
			u := math.Round(float64(f[i][j].U * TableC[j%8][i%8]))
			v := math.Round(float64(f[i][j].V * TableC[j%8][i%8]))
			f[i][j].Set(int(y), int(u), int(v))
		}
	}
}
