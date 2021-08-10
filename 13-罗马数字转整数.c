/********************************************************
 * 罗马数字包含以下七种字符: I， V， X， L，C，D 和 M。
 *
 * 字符          数值
 * I             1
 * V             5
 * X             10
 * L             50
 * C             100
 * D             500
 * M             1000
 * 例如， 罗马数字 2 写做 II ，即为两个并列的 1。12 
 * 写做 XII ，即为 X + II 。 27 写做  XXVII, 即为 XX + V + II 。
 *
 * 通常情况下，罗马数字中小的数字在大的数字的右边。
 * 但也存在特例，例如 4 不写做 IIII，而是 IV。数字 1 在
 * 数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的
 * 数值 4 。同样地，数字 9 表示为 IX。这个特殊的规
 * 则只适用于以下六种情况：
 *
 * I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
 * X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。 
 * C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。
 * 给定一个罗马数字，将其转换成整数。输入确保在 1 到 3999 的范围内。
 * ******************************************************/

#include "stdio.h"
#include "stdlib.h"

/**
 * 解题思路：一个数值中，字母排序都是按照大小顺序排列的，也就是
 * 表示数值大的字母在前，小的在后，也有例外的情况，小的在大的前面
 * 这个表示减去小的数值。按照此规律，只需要比对字母代表的数值大小
 * 按照其顺序决定是+还是-。
 *
 * 小tips：如果都是字符的问题，可以定义数组，利用字母的有序性来
 * 辅助定位下标
 */
int romanToInt(char * s)
{
	int		i = 0;
	int		rst = 0;
	int		value_list[26] = {0};
	value_list['I'-'A'] = 1;
	value_list['V'-'A'] = 5;
	value_list['X'-'A'] = 10;
	value_list['L'-'A'] = 50;
	value_list['C'-'A'] = 100;
	value_list['D'-'A'] = 500;
	value_list['M'-'A'] = 1000;

	if (!s) return 0;
	for (i = 0; s[i+1] != 0; ++i) {
		if (value_list[s[i]-'A'] >= value_list[s[i+1]-'A'])
			rst += value_list[s[i]-'A'];
		else
			rst -= value_list[s[i]-'A'];
	}
	rst += value_list[s[i]-'A'];
	return rst;
}

int main(int argc, char* argv[])
{
	printf("num = %d\r\n", romanToInt(argv[1]));	
	return 0;
}
