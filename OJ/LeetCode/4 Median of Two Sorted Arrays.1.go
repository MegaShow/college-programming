package main

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
