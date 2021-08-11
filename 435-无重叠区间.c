/********************************************************
 * 给定一个区间的集合，找到需要移除区间的最小数量，使剩余区间互不重叠。
 *
 * 注意:
 * 
 * 可以认为区间的终点总是大于它的起点。
 * 区间 [1,2] 和 [2,3] 的边界相互“接触”，但没有相互重叠。
 * *******************************************************/

#include <stdlib.h>
#include <stdio.h>

int compare_int(void* num1, void* num2)
{
    return ((int*)(*(int**)num1))[1] - ((int*)(*(int**)num2))[1];
}

/**
 * 注意这个题中的intervals参数, 是一个二级指针，在访问是要注意。
 * 在快排的回调函数中要注意指针的转换，和值的访问。
 *
 * 这道题目是贪心算法的典型案例，局部最优解，就是全局最优解
 */
int eraseOverlapIntervals(int** intervals, int intervalsSize, int* intervalsColSize)
{
    int     i = 0;
    int     tail_min = 0;
    int     del_num = 0;
    
    qsort(intervals, intervalsSize, sizeof(void*), compare_int);

    for (i = 0; i < intervalsSize; ++i) {
        printf("%d %d\r\n", intervals[i][0], intervals[i][1]);
    }
    printf("\r\n");
    tail_min = intervals[0][1];
    for (i = 1; i < intervalsSize; ++i) {
        if (intervals[i][0] < tail_min)
            ++del_num;
        else 
            tail_min = intervals[i][1];
    }

    return del_num;
}


int main(int argc, char* argv[])
{
    int del_num = 0;
    int* num_list[4] = {0};
    int i = 0;

    for (i = 0; i < 4; ++i) {
        num_list[i] = calloc(1, sizeof(int)*2);
    }
    num_list[0][0] = 1;
    num_list[0][1] = 100;

    num_list[1][0] = 11;
    num_list[1][1] = 22;

    num_list[2][0] = 1;
    num_list[2][1] = 11;

    num_list[3][0] = 2;
    num_list[3][1] = 12;
        
    printf("%d\r\n", eraseOverlapIntervals((int**)num_list, 4, &del_num));
}
