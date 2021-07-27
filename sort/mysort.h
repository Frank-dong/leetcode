#ifndef __MYSORT_H__
#define __MYSORT_H__

int bubble_sort(int* nums, int numsSize);
int bubble_sort_d(void* nums, int unit_size, int numsSize, 
                            int (*compar)(void*, void*));

#endif
