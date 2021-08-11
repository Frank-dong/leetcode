/********************************************************
 * 给你两个 非空 的链表，表示两个非负的整数。它们每位数字
 * 都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。
 *
 * 请你将两个数相加，并以相同形式返回一个表示和的链表。
 *
 * 你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
 * ******************************************************/


/**
 * 这道题审题完成后会发现，其实就是正常的整数相加的计算过程
 * 链表的顺序就是按照低位到高位组成的，所以从两个链表的第一个
 * 节点元素开始相加，在加的过程中需要注意进位.
 *
 * 在写代码时可以近似的将NULL节点视为数值0，来方便写代码计算
 */
#include "stdio.h"
#include "stdlib.h"
#include "tools.h"

struct ListNode {
	int val;
	struct ListNode *next;
};
 

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
	struct ListNode* head = NULL;
	struct ListNode* cur = NULL;
	struct ListNode* next = NULL;
	int	add_num = 0;
	int	tmp_num = 0;

	if (!l1 && !l2) {
		return NULL;
	}

	while (l1 || l2 || add_num) {
		if (head == NULL) {
			head = calloc(1, sizeof(struct ListNode));
			cur = head;
			next = cur;
		} else {
			next = calloc(1, sizeof(struct ListNode));
			cur->next = next;
			cur = next;
		}
		tmp_num = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + add_num;
		next->val = tmp_num % 10;
		add_num = tmp_num / 10;
		l1 = l1 ? l1->next : NULL;
		l2 = l2 ? l2->next : NULL;
	}
	return head;
}

/**
 * 下面的方式其实就是用递归代替了循环而已，使用一个静态的局部变量来保存
 * 进位值
 */
struct ListNode* addTwoNumbers_dg(struct ListNode* l1, struct ListNode* l2){
	struct ListNode* head = NULL;
	static int add_num = 0;
	int	tmp_num = 0;

	if (!l1 && !l2) {
		return NULL;
	}

	head = calloc(1, sizeof(struct ListNode));
	tmp_num = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + add_num;
	head->val = tmp_num % 10;
	add_num = tmp_num / 10;
	head->next = addTwoNumbers_dg(l1 ? l1->next : NULL, l2 ? l2->next : NULL);

	return head;
}

int main(int argc, char* argv[])
{
	struct ListNode*	l1 = NULL;
	struct ListNode*	l2 = NULL;
	struct ListNode*	tmp = NULL;
	struct ListNode*	next = NULL;
	struct ListNode*	list = NULL;
	int*	array_1 = NULL;
	int*	array_2 = NULL;
	int	l1_num = 0;
	int	l2_num = 0;
	int	i = 0;

	if (argc != 3) {
		return -1;
	}
	
	l1_num = atoi(argv[1]);
	l2_num = atoi(argv[2]);	

	array_1 = calloc(1, sizeof(int)*l1_num);
	array_2 = calloc(1, sizeof(int)*l2_num);
	create_nums(array_1, l1_num, 1, 9);	
	create_nums(array_2, l2_num, 1, 9);	

	for (i = 0; i < l1_num; ++i) {
		if (!l1) {
			l1 = calloc(1, sizeof(struct ListNode));
			l1->val = array_1[i];
			tmp = l1;
		} else {
			next = calloc(1, sizeof(struct ListNode));
			next->val = array_1[i];
			tmp->next = next;
			tmp = next;
		}
	}

	for (i = 0; i < l2_num; ++i) {
		if (!l2) {
			l2 = calloc(1, sizeof(struct ListNode));
			l2->val = array_2[i];
			tmp = l2;
		} else {
			next = calloc(1, sizeof(struct ListNode));
			next->val = array_2[i];
			tmp->next = next;
			tmp = next;
		}
	}

	printf("list_1: ");
	tmp = l1;
	while (tmp) {
		printf("%d ", tmp->val);
		tmp = tmp->next;
	}		
	printf("\r\n");
	printf("list_2: ");
	tmp = l2;
	while (tmp) {
		printf("%d ", tmp->val);
		tmp = tmp->next;
	}		
	printf("\r\n");
	

	list = addTwoNumbers(l1, l2);
	printf("list_rst: ");
	tmp = list;
	while (tmp) {
		printf("%d ", tmp->val);
		tmp = tmp->next;
	}		
	printf("\r\n");

	list = addTwoNumbers_dg(l1, l2);
	printf("list_dg : ");
	tmp = list;
	while (tmp) {
		printf("%d ", tmp->val);
		tmp = tmp->next;
	}		
	printf("\r\n");
}
