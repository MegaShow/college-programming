package main

// Solution 1
func findMedianSortedArrays(nums1 []int, nums2 []int) float64 {
	m, n := len(nums1), len(nums2)
	if m == 1 && n == 0 {
		return float64(nums1[0])
	} else if m == 0 && n == 1 {
		return float64(nums2[0])
	}
	skip := (m+n+1)/2 + 1
	var lhs1, lhs2, val1, val2 int
	var i int
	for i = 0; i < skip && lhs1 < m && lhs2 < n; i++ {
		val2 = val1
		if nums1[lhs1] <= nums2[lhs2] {
			val1 = nums1[lhs1]
			lhs1++
		} else {
			val1 = nums2[lhs2]
			lhs2++
		}
	}
	for i < skip && lhs1 >= m {
		val2 = val1
		val1 = nums2[lhs2]
		lhs2++
		i++
	}
	for i < skip && lhs2 >= n {
		val2 = val1
		val1 = nums1[lhs1]
		lhs1++
		i++
	}
	if (m+n)%2 == 0 {
		return float64(val1+val2) / 2
	}
	return float64(val2)
}

// Solution 2
func findMedianSortedArrays(nums1 []int, nums2 []int) float64 {
	m, n := len(nums1), len(nums2)
	if (m+n)%2 != 0 {
		return float64(findKthSmallestNumber(nums1, nums2, (m+n)/2+1))
	}
	return float64(findKthSmallestNumber(nums1, nums2, (m+n)/2)+findKthSmallestNumber(nums1, nums2, (m+n)/2+1)) / 2
}

func findKthSmallestNumber(nums1, nums2 []int, k int) int {
	m, n := len(nums1), len(nums2)
	if m == 0 {
		return nums2[k-1]
	}
	if n == 0 {
		return nums1[k-1]
	}
	if k == 1 {
		return min(nums1[0], nums2[0])
	}
	if m < k/2 {
		return findKthSmallestNumber(nums1, nums2[k/2:], k-k/2)
	}
	if n < k/2 {
		return findKthSmallestNumber(nums1[k/2:], nums2, k-k/2)
	}
	if nums1[k/2-1] < nums2[k/2-1] {
		return findKthSmallestNumber(nums1[k/2:], nums2, k-k/2)
	} else {
		return findKthSmallestNumber(nums1, nums2[k/2:], k-k/2)
	}
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

// Solution 3
import "math"

func findMedianSortedArrays(nums1 []int, nums2 []int) float64 {
	m, n := len(nums1), len(nums2)
	if m == 1 && n == 0 {
		return float64(nums1[0])
	} else if m == 0 && n == 1 {
		return float64(nums2[0])
	}
	nums1, nums2 = append(nums1, math.MaxInt64), append(nums2, math.MaxInt64)
	min1, min2 := findKthSmallestNumber(nums1, nums2, (m+n)/2)
	if (m+n)%2 != 0 {
		return float64(min2)
	}
	return float64(min1 + min2) / 2
}

func findKthSmallestNumber(nums1, nums2 []int, k int) (int, int) {
	m, n := len(nums1) - 1, len(nums2) - 1
	if m == 0 {
		return nums2[k-1], nums2[k]
	}
	if n == 0 {
		return nums1[k-1], nums1[k]
	}
	if k == 1 {
		return min(nums1[0], nums1[1], nums2[0], nums2[1])
	}
	if m < k/2 {
		return findKthSmallestNumber(nums1, nums2[k/2:], k-k/2)
	}
	if n < k/2 {
		return findKthSmallestNumber(nums1[k/2:], nums2, k-k/2)
	}
	if nums1[k/2-1] < nums2[k/2-1] {
		return findKthSmallestNumber(nums1[k/2:], nums2, k-k/2)
	} else {
		return findKthSmallestNumber(nums1, nums2[k/2:], k-k/2)
	}
}

func min(a1, a2, b1, b2 int) (int, int) {
	if a1 <= b1 && a2 <= b1 {
		return a1, a2
	} else if a1 <= b1 {
		return a1, b1
	} else if a1 <= b2 {
		return b1, a1
	}
	return b1, b2
}

// Solution 4
func findMedianSortedArrays(nums1 []int, nums2 []int) float64 {
	m, n := len(nums1), len(nums2)
	if m > n {
		m, n, nums1, nums2 = n, m, nums2, nums1
	}
	iMin, iMax := 0, m
	for iMin <= iMax {
		i := (iMin + iMax) / 2
		j := (m+n+1)/2 - i
		if i > 0 && nums1[i-1] > nums2[j] {
			iMax = i - 1
		} else if i < m && nums1[i] < nums2[j-1] {
			iMin = i + 1
		} else {
			var leftMax, rightMin int
			if i == 0 {
				leftMax = nums2[j-1]
			} else if j == 0 {
				leftMax = nums1[i-1]
			} else {
				leftMax = max(nums1[i-1], nums2[j-1])
			}
			if (m+n)%2 != 0 {
				return float64(leftMax)
			}
			if i == m {
				rightMin = nums2[j]
			} else if j == n {
				rightMin = nums1[i]
			} else {
				rightMin = min(nums1[i], nums2[j])
			}
			return float64(leftMax+rightMin) / 2
		}
	}
	return 0
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
