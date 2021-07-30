#ifndef __MYSORT_H__
#define __MYSORT_H__

void show_nums(int* nums, int nums_size);

int bubble_sort(int* nums, int numsSize);
int bubble_sort_d(void* nums, int unit_size, int numsSize, 
                            int (*compar)(void*, void*));

int quick_sort(int* nums, int begin, int end);
int select_sort(int* nums, int numsSize);
int	insert_sort(int* nums, int numsSize);
int shell_sort(int* nums, int numsSize);
int merge_sort(int* nums, int numsSize);
int count_sort(int* nums, int numsSize);
int randix_sort(int* nums, int numsSize);

#endif
