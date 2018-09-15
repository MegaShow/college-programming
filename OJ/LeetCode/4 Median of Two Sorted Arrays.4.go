package main

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
