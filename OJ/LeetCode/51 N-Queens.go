package main

// Solution 1
import "strings"

func solveNQueens(n int) (res [][]string) {
	chessboard := make([]string, n)
	for i := 0; i < n; i++ {
		chessboard[i] = strings.Repeat(".", n)
	}
	dfs(0, n, chessboard, &res)
	return
}

func dfs(depth, n int, chessboard []string, res *[][]string) {
	if depth == n {
		dst := make([]string, n)
		copy(dst, chessboard)
		*res = append(*res, dst)
		return
	}
	for j := 0; j < n; j++ {
		if isValid(depth, n, j, chessboard) {
			str := []rune(chessboard[depth])
			str[j] = 'Q'
			chessboard[depth] = string(str)
			dfs(depth+1, n, chessboard, res)
			str[j] = '.'
			chessboard[depth] = string(str)
		}
	}
}

func isValid(depth, n, j int, chessboard []string) bool {
	for i := 1; i <= depth; i++ {
		if chessboard[depth-i][j] == 'Q' {
			return false
		} else if j-i >= 0 && chessboard[depth-i][j-i] == 'Q' {
			return false
		} else if j+i < n && chessboard[depth-i][j+i] == 'Q' {
			return false
		}
	}
	return true
}

// Solution 2
import "strings"

func solveNQueens(n int) (res [][]string) {
	chessboard := make([]string, n)
	visit := make([][]bool, 3)
	visit[0] = make([]bool, n)
	visit[1] = make([]bool, 2*n-1)
	visit[2] = make([]bool, 2*n-1)
	for i := 0; i < n; i++ {
		chessboard[i] = strings.Repeat(".", n)
	}
	dfs(0, n, visit, chessboard, &res)
	return
}

func dfs(depth, n int, visit [][]bool, chessboard []string, res *[][]string) {
	if depth == n {
		dst := make([]string, n)
		copy(dst, chessboard)
		*res = append(*res, dst)
		return
	}
	for j := 0; j < n; j++ {
		if !visit[0][j] && !visit[1][n-1-depth+j] && !visit[2][depth+j] {
			str := []rune(chessboard[depth])
			str[j] = 'Q'
			chessboard[depth] = string(str)
			visit[0][j], visit[1][n-1-depth+j], visit[2][depth+j] = true, true, true
			dfs(depth+1, n, visit, chessboard, res)
			str[j] = '.'
			chessboard[depth] = string(str)
			visit[0][j], visit[1][n-1-depth+j], visit[2][depth+j] = false, false, false
		}
	}
}
