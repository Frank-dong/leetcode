#include <stdio.h>
#include <stdlib.h>

/**
 * 冒泡排序 (升序)
 */
int bubble_sort(int* nums, int numsSize)
{
    int i = 0;
    int j = 0;
    int tmp = 0;

    printf("%d\r\n", numsSize);
    for (i = 0; i < numsSize-1; ++i) {
        for (j = i + 1; j < numsSize; ++j) {
            if (nums[i] > nums[j]) {
                tmp = nums[i];
                nums[i] = nums[j];
                nums[j] = tmp;
            }
        }
    }

    return 0;
}

/**
 * 记录一个错误：
 * 如果宏定义中的__unit_size 换成 unit_size
 * 运行程序就会报错。通过预编译结果可以看出，
 * 在最终的代码块中，会在循环体中出现
 * int unit_size = unit_size; 这样的代码。而
 * 此时这个unit_size就是一个随机值，引发错误。
 * 所以在定义宏函数里面的变量名时，最好使用通常
 * 代码中不建议使用的命名方式，比如加下划线的
 * 方式，从而避免宏函数中的变量名与原有变量名
 * 冲突
 */ 
#define SWAP_BY_BYTE(a, b, size)    \
do {                                \
    int     __unit_size = (size);   \
    char*   __pa = (a), *__pb = (b);    \
    char    __tmp;                    \
    do {                            \
        __tmp = *__pa;                  \
        *__pa++ = *__pb;                \
        *__pb++ = __tmp;                \
    } while (--__unit_size > 0);          \
} while (0)

void swap_func(void* a, void* b, int size)
{
    int     unit_size = size;     
    char*   pa = a, *pb = b;    
    char    tmp;                   
    do {                            
        printf("tmp = 0x%x, pa = 0x%x\r\n", tmp, pa);   
        tmp = *pa;                 
        *pa++ = *pb;               
        *pb++ = tmp;               
    } while (--unit_size > 0);      
}
/**
 * 冒泡排序，自定义升序或降序
 * 上面的算法的缺点是只能针对固定类型的数据，并且
 * 顺序方向固定
 * 
 * 改进为：增加单元大小参数和比较函数，这样就将数
 * 据类型和顺序方向解耦，交给用户。
 * 规定：如果升序排列，则compar返回比较数1和比较
 * 数2做差的结果；如果是降序排列，做返回做差结果
 * 符号取反
 * 
 * 这里面有个问题，在交换的时候，由于不知道数值单
 * 元的大小，而交换时需要一个临时空间，如果不动态
 * 申请空间的话，可以采用单个字节来完成多字节的交
 * 换
 */
int bubble_sort_d(void* nums, int unit_size, int numsSize, 
                            int (*compar)(void*, void*))
{
    int i = 0;
    int j = 0;

    for (i = 0; i < numsSize-1; ++i) {
        for (j = i + 1; j < numsSize; ++j) {
            if (compar((char*)nums+i*unit_size, (char*)nums+j*unit_size) > 0) {
                SWAP_BY_BYTE((char*)nums+i*unit_size, 
                    (char*)nums+j*unit_size, unit_size);
            }
        }
    }

    return 0;
}

