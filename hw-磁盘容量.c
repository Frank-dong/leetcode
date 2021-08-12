/********************************************************
 * 磁盘的容量单位有M、G、T，其关系为 1T = 1000G、1G = 1000M，
 * 如样例所示先输入磁盘的个数，再依次输入磁盘的容量大小，
 * 然后按照从小到大的顺序对磁盘容量进行排序并输出。
 * ******************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 首先这是个排序问题，可以选择最简单的冒泡排序，也可选择更加
 * 高效的快速排序。
 * 此题目中排序的数值有所改变，相当于自定义的数表示方法。所以
 * 为了方便比较，需要做一个转换，转换成正常的数值来比较.
 *
 * 可以选择在一开始就将所有的字符串描述转换成以M或者G为单位的
 * 数值描述，然后再排序
 */

struct zone_info {
	int	index;
	double val;	
};


void trans_to_G(char* str, struct zone_info* zone)
{
	char	tail = 0;
	int		num = 0;

	tail = str[strlen(str)-1];
	num = atoi(str);
	if (tail == 'G') {
		zone->val = num;	
	} else if (tail == 'T') {
		zone->val = num*1000;
	} else if (tail == 'M') {
		zone->val = ((double)num)/1000;
	} else {
		zone->val = -1;
	}
}

void zone_quick_sort(struct zone_info* val_list, int start, int end)
{
	struct zone_info	mid = {0};
	int	l = start;
	int	r = end;

	if (end <= start || start < 0)
		return ;
	mid.index = val_list[start].index;
	mid.val = val_list[start].val;
	while (l < r) {
		while (l < r && (val_list[r].val >= mid.val)) {
			r--;
		}
		if (l < r) {
			val_list[l].val = val_list[r].val;
			val_list[l].index = val_list[r].index;
			l++;
		}
		
		while (l < r && (val_list[l].val <= mid.val)) {
			l++;
		}
		if (l < r) {
			val_list[r].val = val_list[l].val;
			val_list[r].index = val_list[l].index;
			r--;
		}
	}

	val_list[l].val = mid.val;
	val_list[l].index = mid.index;
	
	zone_quick_sort(val_list, start, l - 1);
	zone_quick_sort(val_list, l + 1, end);
}

int zone_sort(char** str_list, int size)
{
	struct zone_info	val_list[size];
	char*	backup[size];
	int	i = 0;
	int	j = 0;

	memset(val_list, 0, sizeof(struct zone_info)*size);

	for (i = 0, j = 0; i < size; ++i) {
		backup[i] = str_list[i];
		trans_to_G(str_list[i], &val_list[j]);
		if (val_list[j].val == -1) {	// 无效的数值
			continue;	
		}
		val_list[j].index = i;
		j++;
	}
	zone_quick_sort(val_list, 0, j - 1);
	
	for (i = 0; i < j; ++i) {
		str_list[i] = backup[val_list[i].index];
	}
	return j;
}


int main(int argc, char* argv[])
{
	char*	str_list[] = {
		"3",
		"5G",
		"2T",
		"3M",
		"200M",
		"300G",
		"2T",
		"20G"
	};
	int	ret = 0;
	int	i = 0;

	ret = zone_sort(str_list, 8);

	for (i = 0; i < ret; ++i) {
		printf("%s\r\n", str_list[i]);
	}
}
