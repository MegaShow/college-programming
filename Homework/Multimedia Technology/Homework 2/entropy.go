package main

type AC struct {
	RunLength uint
	Size      uint
	Value     int32
}

type YUVAC struct {
	Y []AC
	U []AC
	V []AC
}

type DC struct {
	Size      uint
	Amplitude int32
}

type YUVDC struct {
	Y DC
	U DC
	V DC
}

func (dc *YUVDC) Set(y, u, v int32) {
	dc.Y.Size, dc.U.Size, dc.V.Size = getSize(y), getSize(u), getSize(v)
	dc.Y.Amplitude, dc.U.Amplitude, dc.V.Amplitude = y, u, v
}

type Bits struct {
	Data []byte
	Pos  int
}

func (b *Bits) AppendString(str string) *Bits {
	if b.Pos != 0 {
		for len(str) != 0 && b.Pos < 8 {
			b.Data[len(b.Data)-1] <<= 1
			b.Data[len(b.Data)-1] |= str[0] - '0'
			b.Pos++
			str = str[1:]
		}
	}
	for len(str)/8 != 0 {
		bv := str[0] - '0'
		for i := 1; i < 8; i++ {
			bv <<= 1
			bv |= str[i] - '0'
		}
		b.Data = append(b.Data, bv)
		str = str[8:]
	}
	b.Pos = len(str)
	if b.Pos != 0 {
		bv := str[0] - '0'
		str = str[1:]
		for len(str) != 0 {
			bv <<= 1
			bv |= str[0] - '0'
			str = str[1:]
		}
		b.Data = append(b.Data, bv)
	}
	return b
}

func (b *Bits) AppendInt32(value int32, size uint) *Bits {
	for i := uint(1); i <= size; i++ {
		if b.Pos == 8 {
			b.Data = append(b.Data, 0)
			b.Pos = 0
		} else {
			b.Data[len(b.Data)-1] <<= 1
		}
		if value>>(size-i)&1 == 1 {
			b.Data[len(b.Data)-1] |= 1
		}
	}
	return b
}

func Entropy(f [][]YUVDCT) (bytes []byte) {
	ac, dc := getACAndDC(f)
	arrAc, arrDc := getACArray(ac), getDCArray(dc)
	treeAc, treeDc := GetHuffmanTree(arrAc), GetHuffmanTree(arrDc)
	tableAc, tableDc := GetHuffmanTableMap(treeAc), GetHuffmanTableMap(treeDc)
	var b Bits
	encodeAc(ac, tableAc, &b)
	encodeDc(dc, tableDc, &b)
	return b.Data
}

func getACAndDC(f [][]YUVDCT) (ac [][]YUVAC, dc [][]YUVDC) {
	ac, dc = make([][]YUVAC, len(f)/8), make([][]YUVDC, len(f)/8)
	for i := 0; i < len(f)/8; i++ {
		ac[i], dc[i] = make([]YUVAC, len(f[i])/8), make([]YUVDC, len(f[i])/8)
		for j := 0; j < len(f[i*8])/8; j++ {
			for x, y := 0, 0; x < 8 && y < 8; {
				if x == 0 && y == 0 {
					dpcm(&dc[i][j], f[i*8][j*8], dc[0][0])
				} else {
					rlc(&ac[i][j].Y, int32(f[i*8+x][j*8+y].Y))
					rlc(&ac[i][j].U, int32(f[i*8+x][j*8+y].U))
					rlc(&ac[i][j].V, int32(f[i*8+x][j*8+y].V))
				}
				if (y == 0 || y == 7) && x%2 == 0 {
					x++
				} else if (x == 0 || x == 7) && y%2 == 1 {
					y++
				} else if (x+y)%2 == 0 {
					x++
					y--
				} else {
					x--
					y++
				}
			}
			makeEndToRlc(&ac[i][j].Y)
			makeEndToRlc(&ac[i][j].U)
			makeEndToRlc(&ac[i][j].V)
		}
	}
	return
}

func rlc(ac *[]AC, value int32) {
	if len(*ac) == 0 {
		*ac = append(*ac, AC{RunLength: 0, Value: 0})
	}
	if value != 0 {
		(*ac)[len(*ac)-1].Value = value
		(*ac)[len(*ac)-1].Size = getSize(value)
		*ac = append(*ac, AC{})
	} else {
		if (*ac)[len(*ac)-1].RunLength == 15 {
			*ac = append(*ac, AC{})
		}
		(*ac)[len(*ac)-1].RunLength++
	}
}

func makeEndToRlc(ac *[]AC) {
	if (*ac)[len(*ac)-1].RunLength != 0 || (*ac)[len(*ac)-1].Value != 0 {
		*ac = append(*ac, AC{})
	}
}

func dpcm(dc *YUVDC, f YUVDCT, baseDc YUVDC) {
	dcy := int32(f.Y) - baseDc.Y.Amplitude
	dcu := int32(f.U) - baseDc.U.Amplitude
	dcv := int32(f.V) - baseDc.V.Amplitude
	dc.Set(dcy, dcu, dcv)
}

func getSize(value int32) uint {
	if value < 0 {
		value = -value
	}
	var i uint
	for i = 31; i > 0; i-- {
		if value>>i&1 != 0 {
			return i + 1
		}
	}
	return 1
}

func getACSymbol1(ac AC) uint {
	return (ac.RunLength&0xf)<<4 | (ac.Size & 0xf)
}

func getACArray(ac [][]YUVAC) (arr []uint) {
	for _, i := range ac {
		for _, j := range i {
			for _, k := range j.Y {
				arr = append(arr, getACSymbol1(k))
			}
			for _, k := range j.U {
				arr = append(arr, getACSymbol1(k))
			}
			for _, k := range j.V {
				arr = append(arr, getACSymbol1(k))
			}
		}
	}
	return
}

func getDCArray(dc [][]YUVDC) (arr []uint) {
	for _, i := range dc {
		for _, j := range i {
			arr = append(arr, j.Y.Size, j.U.Size, j.V.Size)
		}
	}
	return
}

func encodeAc(ac [][]YUVAC, table map[uint]string, b *Bits) string {
	var res string
	for _, i := range ac {
		for _, j := range i {
			for _, k := range j.Y {
				b.AppendString(table[getACSymbol1(k)]).AppendInt32(k.Value, k.Size)
			}
			for _, k := range j.U {
				b.AppendString(table[getACSymbol1(k)]).AppendInt32(k.Value, k.Size)
			}
			for _, k := range j.V {
				b.AppendString(table[getACSymbol1(k)]).AppendInt32(k.Value, k.Size)
			}
		}
	}
	return res
}

func encodeDc(dc [][]YUVDC, table map[uint]string, b *Bits) string {
	var res string
	for _, i := range dc {
		for _, j := range i {
			b.AppendString(table[j.Y.Size]).AppendInt32(j.Y.Amplitude, j.Y.Size)
			b.AppendString(table[j.U.Size]).AppendInt32(j.U.Amplitude, j.U.Size)
			b.AppendString(table[j.V.Size]).AppendInt32(j.V.Amplitude, j.V.Size)
		}
	}
	return res
}
