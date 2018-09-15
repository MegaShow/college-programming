package main

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
