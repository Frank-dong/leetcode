/********************************************************
 * 给你单链表的头指针 head 和两个整数 left 和 right ，其中
 *  left <= right 。请你反转从位置 left 到位置 right 的链
 * 表节点，返回 反转后的链表 。
 *
 * 根据题目中的示例可以看到，给出的left和right都是从1开始
 * 计数的.也就是头节点不参与反转
 *
 * 注意：
 * 链表中节点数目为 n
 * 1 <= n <= 500
 * -500 <= Node.val <= 500
 *  1 <= left <= right <= n
 * ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * 涉及到反转问题，首先可以想到用栈来处理，第一遍遍历到left
 * 位置后，开始入栈，知道right，然后出栈拼接到原链表.
 *
 * 或者到达left后，直接开始遍历反转，修改指针，也可以实现。
 *
 * 第三种方法可以使用
 */

struct ListNode {
	int	val;
	struct ListNode* next;
};


/**
 * 利用递归，反转整个链表
 */
struct ListNode* reverseAll(struct ListNode* head)
{
	struct ListNode*	new_head = NULL;

	// 退出条件
	if (head->next == NULL) {
		return head;
	}
	/**
	 * 先将后后面链表视为一个整体，下面四行就相当于是两个节点的
	 * 反转. 其中后半部反转递归调用此函数，完成所有节点的反转
	 * new_head = xxx;
	 * head->next->next = head;
	 * head->next = NULL;
	 * return new_head;
	 */
	new_head = reverseAll(head->next);
	head->next->next = head;
	head->next = NULL;
	return new_head;
}

/**
 * 这个接口是从链表开始翻转前n节点, 所以期待返回的是反转后的
 * 链表的头节点.
 */
struct ListNode* g_last = NULL;
struct ListNode* reverseN(struct ListNode* head, int n)
{
	struct ListNode* node = NULL;

	if (n == 1) {
		g_last = head->next;
		return head;
	}

	// 获取到子链表翻转后的头节点
	node = reverseN(head->next, n-1);

	// 原头节点反转
	head->next->next = head;

	// 原头节点的后继节点指向反转截断的地方
	head->next = g_last;

	// 返回新的头节点
	return node;
}
struct ListNode* reverseBetween(struct ListNode* head, int left, int right)
{
	if (left == 1) {
		return reverseN(head, right);
	}

	head->next = reverseBetween(head->next, left-1, right-1);
	return head;
}

int main(int argc, char* argv[])
{
	int	nums[] = {1, 2, 3, 4, 5, 6, 7,8, 9};	
	struct ListNode*	head = NULL;
	struct ListNode*	node = NULL;
	struct ListNode*	cur = NULL;
	int	i = 0;
	int	len = sizeof(nums)/sizeof(nums[0]);

	for (i = 0; i < len; ++i) {
		node = calloc(1, sizeof(struct ListNode));
		node->val = nums[i];
		node->next = NULL;
		if (head == NULL) {
			head = node;
			cur = head;
		} else {
			cur->next = node;	
			cur = node;
		}
	}

	node = head;
	while (node) {
		printf("%d ", node->val);
		node = node->next;
	}
	printf("\r\n");

#if 0
	struct ListNode* new_head = reverseAll(head);
	node = new_head;
	while (node) {
		printf("%d ", node->val);
		node = node->next;
	}
#else
	reverseBetween(head, atoi(argv[1]), atoi(argv[2]));
	
	node = head;
	while (node) {
		printf("%d ", node->val);
		node = node->next;
	}
#endif
	printf("\r\n");
}
