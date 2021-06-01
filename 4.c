/********************************************************
 * 给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1
 * 和 nums2。请你找出并返回这两个正序数组的 中位数 。
 *
 * 思路：
 * 两个数组已经有序，需要做的就是分别从头开始遍历两个数组
 * 按照正序遍历，找到对应位置的数即可
 * ******************************************************/
#include <stdio.h>

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size)
{
	int		index_1 = 0;
	int		index_2 = 0;
	int		stop_pos = 0;
	int		odd_flag = 0;
	int		tmp = 0;
	double num = 0;
	

	odd_flag = (nums1Size + nums2Size)%2;
	stop_pos = (nums1Size + nums2Size)/2 + odd_flag;

	while ((index_1 + index_2) < stop_pos) {
		if (index_1 >= nums1Size) {
			num = nums2[index_2];
			++index_2;
		} else if (index_2 >= nums2Size) {
			num = nums1[index_1];
			++index_1;
		} else if (nums1[index_1] < nums2[index_2]) {
			num = nums1[index_1];
			++index_1;
		} else {
			num = nums2[index_2];
			++index_2;
		}
	}
	
	if (!odd_flag) {
		if (index_1 >= nums1Size) {
			tmp = nums2[index_2];
		} else if (index_2 >= nums2Size) {
			tmp = nums1[index_1];
		} else if (nums1[index_1] < nums2[index_2]) {
			tmp = nums1[index_1];
		} else {
			tmp = nums2[index_2];
		}

		printf("%f , %d, %f\r\n", num, tmp, (num+tmp)/2);
		num = (num + tmp)/2;
	}
	return num;
}

int main(int argc, char* argv[])
{
	int	num1[] = {1, 10, 15};
	int	num2[] = {8, 9, 12, 14};

	printf("Middle num = %f\r\n", findMedianSortedArrays(num1, 1, num2, 3));
}
