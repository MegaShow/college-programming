package main

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
