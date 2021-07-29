#include <stdio.h>
#include <stdlib.h>

void show_nums(int* nums, int nums_size)
{
    for (int i = 0; i < nums_size; ++i) {
        printf("%d ", nums[i]);
    }
    printf("\r\n");
}

/**
 * 冒泡排序 (升序)
 * 算法时间复杂度是O(n^2)
 * 但其实最好的情况就是本身就是有序的，即
 * 只需要遍历一遍即可，也就是O(n)
 * 此时需要增加一个标志来判断是否发生过
 * 交换
 */
int bubble_sort(int* nums, int numsSize)
{
    int i = 0;
    int j = 0;
    int tmp = 0;
	int swap_flag = 0;

    for (i = 0; i < numsSize-1; ++i) {
        for (j = i + 1; j < numsSize; ++j) {
            if (nums[i] > nums[j]) {
                tmp = nums[i];
                nums[i] = nums[j];
                nums[j] = tmp;
				swap_flag = 1;
            }
        }

		if (swap_flag == 0)
			break;
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
	int swap_flag = 0;

    for (i = 0; i < numsSize-1; ++i) {
        for (j = i + 1; j < numsSize; ++j) {
            if (compar((char*)nums+i*unit_size, 
						(char*)nums+j*unit_size) > 0) {
                SWAP_BY_BYTE((char*)nums+i*unit_size, 
                    (char*)nums+j*unit_size, unit_size);
				swap_flag = 1;
            }
        }
		if (swap_flag == 0)
			break;
    }

    return 0;
}

/**
 * 快速排序 (升序)
 * 快速排序的主要思想是分治，通过一次遍历，将数分为大小
 * 两部分，然后对这两部分再用相同的办法来排序，最终各个 
 * 小的部分有序，这个数列也就是有序的了。
 *
 * 具体操作上是选取一个锚点值，分成大于锚点值和小于锚点
 * 值两部分。记录锚点值后，锚点位置就相当于是一个坑，然
 * 后合适的值往这里填，填值的地方就又空出来了，等待填另
 * 一个数，所以相当于是直接赋值，而没有数值交换。
 *
 * 对边界条件分析的不够，导致前期调试错误
 * 1. [问题点1]在寻找大于或者小于锚点值的地方，不能在
 * while判断条件中使用自增或自减运算，因为接下来要用做比
 * 较的值
 *
 * 2. [问题点2]在填空时没有判断是否已结束的边界，导致填
 * 值后，位置错位。
 *
 * 3. [问题点3]因为有个left-1和left+1的变化，可能会导致
 * 递归参数中出现begin和end不合适的情况，所以需要在函数
 * 开头做参数检查
 *
 * 时间复杂度的计算
 * 根据代码可以看出，每一层的递归操作次数是这一层传入元
 * 素的个数, 
 * 第一层是n次
 * 第二层是2次递归，每次n/2次操作，共n次操作
 * 第三层是4次递归，每次n/4次操作，共n次操作
 * 第K层是2^(k-1)次递归，每次是n/(2^(k-1))次操作
 * 此时树的深度就是K=log_2n(以2为底，n的对数)
 * 每层都是n次操作（忽略每次会减去一个锚值）
 * 所以总的时间复杂度应该是 nlogn
 *
 * 最坏情况是每次分隔的两部分是1和n-1个数，也就是每次遍
 * 厉一遍，只分出一个数，那么总的循环次数就是n + (n-1)+
 * (n-2) + (n-3) + ..+ 1 = n(n-1)/2, 即O(n^2)
 */
int quick_sort(int* nums, int begin, int end)
{
	int	left = begin;
	int	right = end;
	int	anchor = nums[begin];	// 选取锚点值，相当于
								// 锚点位置空出了

	if (!nums || end < begin || begin < 0)
		return 0;

	printf("anchor = %d, begin = %d, end = %d\r\n", anchor, begin, end);
	while (left < right) {
		// 寻找小于锚点值的值来向锚点左边填空
		// 问题点1
		while (left < right && nums[right] >= anchor)
			--right;

		// 问题点2
		if (right > left)
			nums[left++] = nums[right];
		
		// 寻找大于锚点值的值来向锚点右边填空
		while (left < right && nums[left] <= anchor)
			++left;
		if (right > left)
			nums[right--] = nums[left];
	}
	// 将锚点值填入分界位置
	nums[left] = anchor;

	// 对左边部分用同样的方法排序
	// 问题点3
	quick_sort(nums, begin, left - 1);
	quick_sort(nums, left + 1, end);

	return 0;
}

/**
 * 第二遍重写
 */
int quick_sort_d(int* nums, int start, int end)
{
	int	l = start;
	int	r = end;
	int	anchor = nums[start];

	if (!nums || end < start || start < 0)
		return 0;
	while (l < r) {
		while (l < r && nums[r] >= anchor)
			--r;
		if (l < r)
			nums[l++] = nums[r];
		
		while (l < r && nums[l] <= anchor)
			++l;
		if (l < r)
			nums[r--] = nums[l];
	}
	nums[l] = anchor;

	quick_sort_d(nums, start, l - 1);
	quick_sort_d(nums, l + 1, end);
}

/**
 * 选择排序
 * 选择排序的思想是从数列中寻找出最小(大)的值，放在数列前面，组成
 * 有序数列，再次遍历再得到一个最小(大)的值，继续往有序数列后面放
 *
 */
int select_sort(int* nums, int numsSize)
{
	int	i = 0;
	int	tail = 0;
	int	tmp = 0;
	int	target = 0;

	while (tail < numsSize) {
		// 每次选取有序队尾元素为比较对象
		target = tail;
		// 遍历得到最小(大)的值，记录其下标
		for (i = tail + 1; i < numsSize; ++i) {
			if (nums[i] < nums[target]) {
				target = i;
			}
		}
		if (target != tail) {
			// 与有序队尾值进行交换
			tmp = nums[tail];
			nums[tail] = nums[target];
			nums[target] = tmp;
		}
		++tail;
	}
	return 0;
}

/**
 * 选择排序与冒泡排序类似，也是通过比较交换来实现排序，算法复杂度
 * 为O(n^2), 而且每次只是选择其中最小的，并不能判断原数组是否已经
 * 有序，所以没法像冒泡排序那样通过一个是否有序的标志来提前终止排
 * 序. 
 * 由于每次都要遍历一遍无序数组，那么就可以选择一个最大的数和最小
 * 的数，分别从头和尾开始排布，这样可以减少一半的遍历。但是算法复
 * 杂度还是O(n^2).
 */
int select_sort_optimize(int* nums, int numsSize)
{
	int	i = 0;
	int	tail = 0;				// 前半部分序列尾
	int	head = numsSize - 1;	// 后半部分序列头
	int	min_target = tail;
	int	max_target = head;
	int	tmp = 0;

	while (tail <= head) {
		min_target = tail;
		max_target = head;
		// 遍历得到最大值和最小值
		for (i = tail; i <= head; ++i) {
			if (nums[i] < nums[min_target])
				min_target = i;
			if (nums[i] > nums[max_target])
				max_target = i;
		}
		
		if (min_target != tail) {
			// 如果最大值刚好是有序数列队尾，则需要记录下他被交换
			// 的位置
			if (max_target == tail)
				max_target = min_target;

			tmp = nums[tail];
			nums[tail] = nums[min_target];
			nums[min_target] = tmp;
		}

		if (max_target != head) {
			tmp = nums[head];
			nums[head] = nums[max_target];
			nums[max_target] = tmp;
		}

		++tail;
		--head;
	}
	return 0;
}










































