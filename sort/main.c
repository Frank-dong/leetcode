#include <stdio.h>
#include "mysort.h"
#include "../tools.h"



int compare_cb_order(void* num1, void* num2)
{
    return *((int*)num1) - *((int*)num2);
}

int compare_cb_descend(void* num1, void* num2)
{
    return *((int*)num2) - *((int*)num1);
}

//#define SET_NUM
int main(int argc, char* argv[])
{
#ifdef SET_NUM 
    //int nums[] = {1, 0, 5, 9, 2, 4, 15, 89, 0, 23, 2};
    int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int		nums_size = sizeof(nums)/sizeof(nums[0]);
#else	
	int*	nums = NULL;
	int		nums_size = 0;

	if (argc != 4) {
		printf("Usage: %s nums min max\r\n", argv[0]);
		return 0;
	}
	nums_size = atoi(argv[1]);
	nums = calloc(1, sizeof(int)*nums_size);
	create_nums(nums, nums_size, atoi(argv[2]), atoi(argv[3]));
#endif

    //show_nums(nums, nums_size);

	start_time();	
    bubble_sort(nums, nums_size);			//10W个数排序约30s
    //bubble_sort_d(nums, sizeof(int), nums_size, compare_cb_order);
	//quick_sort_d(nums, 0, nums_size - 1);	//10W个数排序约13ms
	//select_sort(nums, nums_size);			//10W个数排序约11s
	//select_sort_optimize(nums, nums_size);//10W个数排序约6s
	stop_time();

    show_nums(nums, nums_size);
#ifndef SET_NUM
	free(nums);
#endif

    return 0;
}
