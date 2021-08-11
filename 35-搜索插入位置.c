/********************************************************
 * 给定一个排序数组和一个目标值，在数组中找到目标值，并返
 * 回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
 *
 * 请必须使用时间复杂度为 O(log n) 的算法。
 * ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 参考链接：
 * https://www.cnblogs.com/kyoner/p/11080078.html
 *
 * 这是一个典型的二分查找的示例，就是通过不断修改左右边界
 * 来缩小定位范围.
 * 这里注意，每次搜素的是[left, right]这样的闭区间，所以
 * while循环的判断条件中是<=, 而不是<
 * 为防止mid越界，最好写成mid = (right-left)/2+left
 *
 * 另外关于这个算法的衍生问题，比如寻找左边界，寻找右
 * 边界的问题，可以参考上面的链接文章。
 */
int search(int* nums, int numsSize, int target)
{
	int	left = 0;
	int	right = numsSize-1;
	int	mid = 0;
	
	while (left <= right) {
		mid = (right - left)/2 + left;
		printf("mid = %d\r\n", mid);
		// 如果在右半部分，更新左边界
		if (target == nums[mid]) {
			break;
		} else if (target < nums[mid]) {
			right = mid - 1;	
		} else { // 如果在左半部分，更新右边界
			left = mid + 1;	
		}
	}
	return nums[mid] == target ? mid : -1;
}

/**
 * 有序序列查找，首先想到二分查找
 * 正常的二分查找是找到了就返回下标，找不到就返回错误，
 * 本题需要找不到也要返回一个合适插入的地方. 所以对于
 * 升序数列来说，就是目标值插入到比它小的值后面，所以
 * 目标位置就要一直紧随有边界，这样的话，如果在左边范围
 * 找不到的话，那插入位置就刚好是刚才记录的右边界
 */
int searchInsert(int* nums, int numsSize, int target)
{
	int	left = 0;
	int	right = numsSize-1;
	int	mid = 0;
	int	pos = numsSize;

	while (left <= right) {
		mid = (right - left)/2 + left;
		if (target == nums[mid]) {
			pos = mid;
			break;
		} else if (target < nums[mid]) {
			pos = mid;
			right--;
		} else if (target > nums[mid]) {
			left++;
		}
	}

	return pos;
}
int main(int argc, char* argv[]) 
{
	int	nums[] = {1, 3, 5, 7, 9, 11, 13, 15, 18, 19};
	int	i = 0;
	for (i = 0; i < sizeof(nums)/sizeof(nums[0]); ++i)
		printf("%d ", nums[i]);

	printf("\r\n");
	printf("mid = %d\r\n", searchInsert(nums, sizeof(nums)/sizeof(nums[0]), atoi(argv[1])));
	//printf("mid = %d\r\n", search(nums, sizeof(nums)/sizeof(nums[0]), atoi(argv[1])));
	return 0;
}
