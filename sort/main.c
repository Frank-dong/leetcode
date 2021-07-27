#include <stdio.h>
#include "mysort.h"


void show_nums(int* nums, int nums_size)
{
    for (int i = 0; i < nums_size; ++i) {
        printf("%d ", nums[i]);
    }
    printf("\r\n");
}

int compare_cb_order(void* num1, void* num2)
{
    return *((int*)num1) - *((int*)num2);
}

int compare_cb_descend(void* num1, void* num2)
{
    return *((int*)num2) - *((int*)num1);
}


int main(int argc, char* argv[])
{
    int nums[] = {1, 0, 5, 9, 2, 4, 15, 89, 0, 23, 2};

    show_nums(nums, sizeof(nums)/sizeof(nums[0]));

    //bubble_sort(nums, sizeof(nums)/sizeof(nums[0]));
    bubble_sort_d(nums, sizeof(int), sizeof(nums)/sizeof(nums[0]), compare_cb_descend);

    show_nums(nums, sizeof(nums)/sizeof(nums[0]));

    return 0;
}
