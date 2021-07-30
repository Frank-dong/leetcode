#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/********************************************************
 * 参考链接：
 * https://www.cnblogs.com/onepixel/articles/7674659.html
 * https://www.cnblogs.com/lqminn/p/3642027.html
 *
 * 排序算法的稳定性：
 * 假定在待排序的数列中有多个相同的数值，经过排序后，这些
 * 相同的数值的相对位置不发生改变，即称之为稳定的排序算法
 * >>冒泡算法是通过相邻数值比较而确定位置的，所以冒泡算法可
 * 做到稳定的排序.如果相等元素也交换的话，就是不稳定的了。
 *
 * >>快速排序由于是不断选取一个值，将待排序列分在两边，所以
 * 相同数值的元素的相对位置在不同轮次的时候可能会变化，所以
 * 是一种不稳定的排序算法。
 * 
 * >>选择排序是通过在无序数列中找出一个最值无序数列第一个值
 * 进行交换，而被交换的无序数列的第一个元素可能与后面某个值
 * 相等，交换后，他们的相对位置就发生了变化。所以也是不稳定的。
 *
 * >>插入排序是后面元素逐个与前面元素进行比较，相同的元素
 * 可以形成边界条件，所以也可以实现稳定的排序。
 *
 * >>希尔排序是插入排序的升级版，通过设置不同的Gap，来加速
 * 比对过程，那么如果相同的元素如果被划分在不同的组，就有可
 * 能发生相对位置变化，所以也是不稳定的。
 *
 * >>归并排序是先将数列打散，然后合并重组，重组过程其实类似
 * 插入排序，所以也是稳定的排序算法。
 *
 * >>计数排序是利用数组下标来记录数值的，可以通过调整记录顺
 * 序和展开顺序来实现稳定的排序. 比如顺序遍历，先记录的，先
 * 展开; 或者逆序遍历，先记录，后展开。
 *
 * >>基数排序类似计数排序类似，所以也是稳定的排序算法。
 * ******************************************************/

void show_nums(int* nums, int nums_size)
{
     for (int i = 0; i < nums_size; ++i) {
          printf("%d ", nums[i]);
     }
     printf("\r\n");
}

/**
 * 冒泡排序 (升序)
 * 冒泡算法的思想是通过比较相邻的两个数，
 * 使得较大(小)的数往后面挪动，这样一趟下来
 * 就会产生无序数列中的最大值排在有序数列的
 * 后面，最后多轮下来就形成了一个升序(降序)
 * 的数列.
 * 这种排序的过程，看起来像下沉。
 * 也可以从后往前遍历，看起来则像上浮(冒泡)
 *
 * 算法时间复杂度是O(n^2)
 * 但其实最好的情况就是本身就是有序的，即
 * 只需要遍历一遍即可,也就是每两个相邻的数值
 * 都没有发生过交换，也就是本身就是有序的，
 * 所以一遍就结束了，也就是O(n)
 * 此时需要增加一个标志来判断是否发生过
 * 交换.
 */
int bubble_sort(int* nums, int numsSize)
{
     int i = 0;
     int j = 0;
     int tmp = 0;
     int swap_flag = 0;

     // 最后只剩下一个数不用比较，所以外层循环
     // 是numsSize-1
     for (i = 0; i < numsSize-1; ++i) {
          // 每经过一轮，就会少一个数值参与比较
          for (j = 0; j < numsSize-1-i; ++j) {
               if (nums[j] > nums[j+1]) {
                    tmp = nums[j];
                    nums[j] = nums[j+1];
                    nums[j+1] = tmp;
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
          for (j = 0; j < numsSize - 1 - i; ++j) {
               if (compar((char*)nums+j*unit_size, 
                              (char*)nums+(j+1)*unit_size) > 0) {
                    SWAP_BY_BYTE((char*)nums+j*unit_size, 
                              (char*)nums+(j+1)*unit_size, unit_size);
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
     int     left = begin;
     int     right = end;
     int     anchor = nums[begin];     // 选取锚点值，相当于
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
     int     l = start;
     int     r = end;
     int     anchor = nums[start];

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
     int     i = 0;
     int     tail = 0;
     int     tmp = 0;
     int     target = 0;

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
     int     i = 0;
     int     tail = 0;                    // 前半部分序列尾
     int     head = numsSize - 1;     // 后半部分序列头
     int     min_target = tail;
     int     max_target = head;
     int     tmp = 0;

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


/**
 * 插入排序(升序)
 * 插入排序的思想是从第一个元素开始，向前对比，寻找合适
 * 的位置插入，这个合适位置就是小于前一个元素，大于后一
 * 个元素。遇到不合适的，就往后移动。
 *
 * 这个算法的时间复杂度与冒泡算法一样，最好情况就是O(n),
 * 最差情况是O(n^2)
 */
int insert_sort(int* nums, int numsSize)
{
     int     current = 0;
     int prev_index = 0;
     int     i = 0;

     for (i = 1; i < numsSize; ++i) {
          current = nums[i];
          prev_index = i - 1;
          // 移动大于目标值的元素
          while (prev_index >= 0 && current < nums[prev_index]) {
               nums[prev_index+1] = nums[prev_index];
               --prev_index;
          }
          // 插入目标值
          nums[prev_index+1] = current;     
     }
     return 0;
}


/**
 * 希尔排序
 * 希尔排序其实也是一种插入排序，是对简单插入排序的一种优化,
 * 上面的插入排序中，每次都是挨个比较。希尔排序的思想就是分
 * 几轮，每轮以不同的间隔来比较，从结果上来看，就是先大体上
 * 有序，再逐步调整，最后达到最终有序.
 *
 * 假设一组数：83 44 15 17 40 74 65 8 84 93
 * 第一轮间隔为5 (nums/2), 相当于将所有数分成5组，每组两个数
 * 进行插入排序。
 * 83 74
 * 44 65
 * 15 8
 * 17 84
 * 40 93
 *
 * 得到 74 44 8 17 40 83 65 15 84 93
 * 第二轮间隔调整为2 (step/=2)，相当于将所有数分成2组，每组
 * 5个数，进行插入排序。
 * 74 8  40 65 84
 * 44 17 83 15 93
 *
 * 得到 8 15 40 17 65 44 74 83 84 93
 * 第三轮间隔调整为1, 相当于最原始的插入排序，但是相比最开始，
 * 数据已经大致有序，调整起来就没有大范围的移动数据了
 *
 * 参考文章：
 * https://www.cnblogs.com/chengxiao/p/6104371.html
 */
int shell_sort(int* nums, int numsSize)
{
     int     step = numsSize/2;
     int     prev_index = 0;
     int     current = 0;
     int     i = 0;
     int     j = 0;

     // 分若干轮来完成
     while (step > 0) {
          // 每轮step组
          for (i = 0; i < step; ++i) {
               // 遍历完每组的值
               for (j = i + step; j < numsSize; j += step) {
                    current = nums[j];
                    prev_index = j - step;
                    while (prev_index >= 0 && current < nums[prev_index]) {
                         nums[prev_index + step] = nums[prev_index];
                         prev_index -= step;
                    }
                    nums[prev_index + step] = current;
               }
          }
          step /= 2;
     }

     return 0;
}


/**
 * 归并排序
 * 归并排序也是分治思想的一种，先将数组拆分成两个小的数组单元，
 * 使其分别有序，然后再合并两个已经有序的数组。其中对于拆分出
 * 来的小的数组单元排序也是利用这个方法，所以可以使用递归的方
 * 式来实现。
 * 拆分的过程好理解，归并的过程就相当于两队已经按大小个排序的
 * 学生按照大小个合并成一个队伍一样，每次从两个队伍中取个字低
 * 的往新队伍后面跟，最终合并成一个队伍。
 *
 * 错误点1:memcpy的第一个参数nums，如果是按照int来步进单元，则
 * 应该是nums+start，如果是强转成char*，步进单位是1，则应该是
 * (char*)nums + start*sizeof(int)
 */

int merge_sort_merge(int* nums, int start, int mid, int end, int* tmp)
{
     int     p1 = start;
     int     p2 = mid + 1;
     int     i = 0;

     //printf("list1: ");
     //show_nums(nums + start, mid - start + 1);
     //printf("list2: ");
     //show_nums(nums + mid + 1, end - mid);
     for (i = 0; p1 <= mid && p2 <= end; ++i) {
          if (nums[p1] < nums[p2]) {
               tmp[i] = nums[p1++];
          } else {
               tmp[i] = nums[p2++];
          }
     }

     if (p1 > mid) {
          while (p2 <= end)
               tmp[i++] = nums[p2++];
     }
     if (p2 > end) {
          while (p1 <= mid) {
               tmp[i++] = nums[p1++];
          }
     }
     // 错误点1
     memcpy((char*)nums + start*sizeof(int), tmp, (end - start + 1)*sizeof(int));
     //memcpy(nums + start, tmp, (end - start + 1)*sizeof(int));
     //printf("merge[%d-%d-%d], end-->", start, mid, end);
     //show_nums(nums+start, end - start + 1);
     return 0;
}
int merge_sort_by_index(int* nums, int start, int end, int* tmp)
{
     if (start >= end) {
          return 0;
     }
     //show_nums(nums, end - start + 1);
     int     mid = (start + end)/2;

     // 先分
     merge_sort_by_index(nums, start, mid, tmp);
     merge_sort_by_index(nums, mid + 1, end, tmp);

     // 后治
     merge_sort_merge(nums, start, mid, end, tmp);
}
int merge_sort(int* nums, int numsSize)
{
     int*     tmp = calloc(1, sizeof(int)*numsSize);
     merge_sort_by_index(nums, 0, numsSize - 1, tmp);

     return 0;
}


/**
 * 计数排序
 * 计数排序的思想是申请一个数组，将数值作为下标，对每个位置
 * 上的数值进行计数，由于数组下标本身就是有序的，所以只需要
 * 遍历一次，就可以把所有值填完，然后再展开即可。所以技术排
 * 序的算法复杂度是O(n).
 * 但是这个算法有一个问题就是空间浪费比较严重，比如[1, 50, 100]
 * 只有三个数的排序，就需要申请100个int型空间。第二个问题就是
 * 这个算法也只适合整数排序,比较受局限。
 *
 * 适用于一些数值跨度不是很大的排序场景
 *
 * 参考文章：
 * https://www.cnblogs.com/xiaochuan94/p/11198610.html
 */
int count_sort(int* nums, int numsSize)
{
     int min = nums[0];
     int     max = nums[0];
     int     i = 0;
     int     j = 0;
     int k = 0;
     int* array = NULL;

     // 第一次遍历找出最大值和最小值
     for (i = 1; i < numsSize; ++i) {
          if (nums[i] > max)
               max = nums[i];
          else if (nums[i] < min)
               min = nums[i];
     }
     if (min == max)
          return 0;

     // 申请一个max-mix+1个整型空间
     array = calloc(1, sizeof(int)*(max - min + 1));

     // 遍历统计不同值的个数(值被记录成了下标)
     for (i = 0; i < numsSize; ++i) {
          array[nums[i]-min] += 1;
     }

     // 将统计个数的数组展开
     for (i = 0; i < (max - min + 1); ++i) {
          for (j = 0; j < array[i]; ++j) {
               // 值就是下标     
               nums[k++] = i + min;     
          }
     }

     free(array);
     return 0;
}



#if 0
/**
 * 桶排序(未完成(分成若干个桶来排序，每个桶中还是需要采用某种方式排序，
 * 只相当于将更大排序分成了几个小段来排序))
 *
 * 桶排序可以看成是对计数排序的一种改进，由于计数排序如果数值
 * 跨度较大，会导致空间浪费比较严重的问题. 所以改进成划分成几
 * 个有序的区间，然后每个区间里面排序，最后再组合
 */
struct bucket_node {
     int val;
     struct bucket_node* next;
};
int bucket_sort(int* nums, int numsSize)
{
     int     i = 0;
     int     step = 0;
     int     bucket_nums = 0;
     int     min = nums[0];
     int     max = nums[0];
     struct bucket_node** bucket_list = NULL;
     struct bucket_node* node = NULL;

     // 第一次遍历找出最大值和最小值
     for (i = 1; i < numsSize; ++i) {
          if (nums[i] > max)
               max = nums[i];
          else if (nums[i] < min)
               min = nums[i];
     }
     if (min == max)
          return 0;

     // 暂时假定使用3个桶
     bucket_nums = 3;
     step = (max - min + 1)/3;

     bucket_list = calloc(1, sizeof(struct bucket_node)*bucket_nums);
     //将数据填入桶中
     for (i = 0; i < numsSize; ++i) {
          bubble_list[]     
     }
}
#endif

/**
 * 基数排序
 * 基数排序的思想是通过设定10个桶，对应的数字就是0~9,                                               
 * 然后对所有数先以个位数字分类放入桶中，然后逐次取出，                                             
 * 完成第一轮。然后以10位数字分类再进行同样的操作，完成                                             
 * 第二轮。直到取到最大值的最高位结束 
 *
 * 错误点1：
 * 重新申请空间时，大小参数错误，只填了个数，没有乘单元大小
 * 错误点2
 * 边界判断错误，导致数组访问越界
 */ 
int randix_sort(int* nums, int numsSize)                                                            
{
     int**   num_list = NULL;
     int     len = numsSize/10;                                                                  
     int     max = nums[0];                                                                      
     int     sort_count = 0;
     int     bucket_index = 0;
     int     i = 0;
     int     j = 0;
     int     k = 0;
     int     exp = 1;

     // 找到最大的数
     for (i = 1; i < numsSize; ++i) {
          if (nums[i] > max)
               max = nums[i];
     }
     printf("max = %d\r\n", max);

     // 申请桶空间
     num_list = calloc(1, sizeof(void*)*10);
     for (i = 0; i < 10; ++i) {
          num_list[i] = calloc(1, (len + 2)*sizeof(int));
          num_list[i][0] = len;   // 记录数组当前长度
          num_list[i][1] = 2;     // 记录下一次要填充位置
     }

     while (max/exp > 0) {
          //show_nums(nums, numsSize);
          // 根据各进制上的数放入桶中
          for (i = 0; i < numsSize; ++i) {
               bucket_index = nums[i]/exp%10;
               // 错误点2
               if (num_list[bucket_index][1] >= num_list[bucket_index][0]+2) {
                    num_list[bucket_index][0] *= 2;
                    // 错误点1
                    num_list[bucket_index] = realloc(num_list[bucket_index], (num_list[bucket_index][0] + 2)*sizeof(int));         
               }
               num_list[bucket_index][num_list[bucket_index][1]++] = nums[i];
          }       

          // 重新排列出来 
          k = 0;
          for (i = 0; i < 10; ++i) {
               for (j = 2; j < num_list[i][1]; j++) {
                    nums[k++] = num_list[i][j];
               }
               num_list[i][1] = 2;
          }
          exp *= 10;
     }
#if 1
     // 释放空间
     for (i = 0; i < 10; ++i) {
          free(num_list[i]);
     }
     free(num_list);
#endif
     return 0;
}






































