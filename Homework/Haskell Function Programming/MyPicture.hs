-------------------------------------------------------------------------
-- Author: Mega Show
-- Date: 2016.10.28 22:00
-- Name: 设计一个放大字符串的程序
-------------------------------------------------------------------------
module MyPicture where
import Data.Char
import Data.List

space = ["  ","  ","  ","  ","  "]
a = ["  A  ",
     " A A ",
     "A   A",
     "AAAAA",
     "A   A"]
b = ["BBBB ",
     "B   B",
     "BBBB ",
     "B   B",
     "BBBB "]
c = [" CCCC",
     "C    ",
     "C    ",
     "C    ",
     " CCCC"]
d = ["DDDD ",
     "D   D",
     "D   D",
     "D   D",
     "DDDD "]
e = ["EEEEE",
     "E    ",
     "EEEEE",
     "E    ",
     "EEEEE"]
f = ["FFFFF",
     "F    ",
     "FFFFF",
     "F    ",
     "F    "]
g = ["GGGGG",
     "G    ",
     "G  GG",
     "G   G",
     "GGGGG"]
h = ["H   H",
     "H   H",
     "HHHHH",
     "H   H",
     "H   H"]
i = ["IIIII",
     "  I  ",
     "  I  ",
     "  I  ",
     "IIIII"]
j = ["  JJJ",
     "    J",
     "    J",
     "J   J",
     " JJJ "]
k = ["K   K",
     "K  K ",
     "KKK  ",
     "K  K ",
     "K   K"]
l = ["L    ",
     "L    ",
     "L    ",
     "L    ",
     "LLLLL"]
m = ["M   M",
     "MM MM",
     "M M M",
     "M M M",
     "M   M"]
n = ["N   N",
     "NN  N",
     "N N N",
     "N  NN",
     "N   N"]
o = [" OOO ",
     "O   O",
     "O   O",
     "O   O",
     " OOO "]
p = ["PPPP ",
     "P   P",
     "PPPP ",
     "P    ",
     "P    "]
q = [" QQQ ",
     "Q   Q",
     "Q   Q",
     " QQQ ",
     "   QQ"]
r = ["RRRR ",
     "R   R",
     "RRRR ",
     "R RR ",
     "R  RR"]
s = ["SSSSS",
     "S    ",
     "SSSSS",
     "    S",
     "SSSSS"]
t = ["TTTTT",
     "  T  ",
     "  T  ",
     "  T  ",
     "  T  "]
u = ["U   U",
     "U   U",
     "U   U",
     "U   U",
     "UUUUU"]
v = ["v   v",
     "v   v",
     "v   v",
     " v v ",
     "  v  "]
w = ["W   W",
     "W W W",
     "W W W",
     "WW WW",
     "W   W"]
x = ["X   X",
     " X X ",
     "  X  ",
     " X X ",
     "X   X"]
y = ["Y   Y",
     " Y Y ",
     "  Y  ",
     "  Y  ",
     "  Y  "]
z = ["ZZZZZ",
     "   Z ",
     "  Z  ",
     " Z   ",
     "ZZZZZ"]
num1 = ["  1  ",
        " 11  ",
        "  1  ",
        "  1  ",
        "11111"]
num2 = [" 222 ",
        "2   2",
        "   2 ",
        "  2  ",
        "22222"]
num3 = ["3333 ",
        "    3",
        " 333 ",
        "    3",
        "3333 "]
num4 = ["   4 ",
        "  44 ",
        " 4 4 ",
        "44444",
        "   4 "]
num5 = ["55555",
        "5    ",
        "55555",
        "    5",
        "55555"]
num6 = ["66666",
        "6    ",
        "66666",
        "6   6",
        "66666"]
num7 = ["77777",
        "   7 ",
        "  7  ",
        " 7   ",
        " 7   "]
num8 = [" 888 ",
        "8   8",
        " 888 ",
        "8   8",
        " 888 "]
num9 = ["99999",
        "9   9",
        "99999",
        "    9",
        "99999"]
num0 = [" 000 ",
        "0   0",
        "0   0",
        "0   0",
        " 000 "]

--将字符放大成字符串数组（即图片）
toListString :: Char -> [String]
toListString str
    |(str == 'A' || str == 'a') = a
    |(str == 'B' || str == 'b') = b
    |(str == 'C' || str == 'c') = c
    |(str == 'D' || str == 'd') = d
    |(str == 'E' || str == 'e') = e
    |(str == 'F' || str == 'f') = f
    |(str == 'G' || str == 'g') = g
    |(str == 'H' || str == 'h') = h
    |(str == 'I' || str == 'i') = i
    |(str == 'J' || str == 'j') = j
    |(str == 'K' || str == 'k') = k
    |(str == 'L' || str == 'l') = l
    |(str == 'M' || str == 'm') = m
    |(str == 'N' || str == 'n') = n
    |(str == 'O' || str == 'o') = o
    |(str == 'P' || str == 'p') = p
    |(str == 'Q' || str == 'q') = q
    |(str == 'R' || str == 'r') = r
    |(str == 'S' || str == 's') = s
    |(str == 'T' || str == 't') = t
    |(str == 'U' || str == 'u') = u
    |(str == 'V' || str == 'v') = v
    |(str == 'W' || str == 'w') = w
    |(str == 'X' || str == 'x') = x
    |(str == 'Y' || str == 'y') = y
    |(str == 'Z' || str == 'z') = z
    |(str == '1') = num1
    |(str == '2') = num2
    |(str == '3') = num3
    |(str == '4') = num4
    |(str == '5') = num5
    |(str == '6') = num6
    |(str == '7') = num7
    |(str == '8') = num8
    |(str == '9') = num9
    |(str == '0') = num0
    |otherwise = []

--将输入的字符串转换成字符串的数组的数组（没有调整位置的输出结果）
toArrayString :: String -> [[String]]
toArrayString [] = []
toArrayString (x:xs) = (toListString x) : (toArrayString xs)

--调整第num-1行输出结果的位置，最终生成字符串
makeNewString :: Int -> [[String]] -> String
makeNewString num [] = []
makeNewString num (x:xs) = (x!!num) ++ "  " ++ (makeNewString num xs)

--将调整的字符串合并成字符串的数组
makeArrayNewString :: [[String]] -> [String]
makeArrayNewString str = (makeNewString 0 str):(makeNewString 1 str)
    :(makeNewString 2 str):(makeNewString 3 str):(makeNewString 4 str):[]

--将输入字符串转换成输出字符串
say :: String -> String
say str = unlines (makeArrayNewString (toArrayString str))

--放大字符串
sayit :: String -> IO()
sayit str = (putStr . say) str
