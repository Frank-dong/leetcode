/********************************************************
 * 给定一个单链表 L 的头节点 head ，单链表 L 表示为：
 *
 *  L0 → L1 → … → Ln-1 → Ln 
 * 请将其重新排列后变为：
 *
 * L0 → Ln → L1 → Ln-1 → L2 → Ln-2 → …
 *
 * 不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
 * ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode {
	int	val;
	struct ListNode* next;
};

void show_list(struct ListNode* list)
{
	struct ListNode* node = list;
	while (node) {
		printf("%d ", node->val);
		node = node->next;
	}
	printf("\r\n");
}

/**
 * 通过示例可以看出，新的链表是前后交错的, 顺序遍历只能遍历到中
 * 间节点，另一部分是从原链表尾部向前遍历的，然后两个链表组合在
 * 一起。
 * 主要问题在于找到中间节点，和后一部分的链表的反转。寻找中间节
 * 点可以采用连个指针，一个步进单位为1，一个为2，等后一个指针到
 * 尾时，前一个指针刚好到中间.
 * 反转链表可以利用栈，也可以直接遍历反转。
 * 
 * 在实际写代码时，需要注意，在寻找到中间节点后，它的前一个节点
 * 的next指针需要修改为NULL，不然跟后一半节点串在一起，在后半部
 * 分翻转后，前半部分多一个节点。
 */
void reorderList(struct ListNode* head)
{
	struct ListNode*	front = NULL;
	struct ListNode*	back = NULL;
	struct ListNode*	tmp = NULL;

	// 找到中间节点以确定后半部分	
	front = head;
	back = head;
	while (back && back->next) {
		front = front->next;
		back = back->next->next;
	}
	back = front->next;
	front->next = NULL;

	// 翻转后半部分的链表
	if (!front || !back)
		return;
	front = back;
	back = front->next;
	front->next = NULL;
	while (back) {
		tmp = back->next;
		back->next = front;
		front = back;
		back = tmp;
	}
	
	// 两个链表融合在一起
	back = front;
	front = head;
	while (front && back) {
		tmp = front->next;
		front->next = back;
		back = back->next;
		front->next->next = tmp;
		front = tmp;
	}

	return ;
}

int main(int argc, char* argv[])
{
	int	nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int	i = 0;
	struct ListNode*	head = NULL;
	struct ListNode*	node = NULL;
	struct ListNode*	prev = NULL;

	for (i = 0; i < sizeof(nums)/sizeof(nums[0]) - atoi(argv[1]); ++i) {
		node = calloc(1, sizeof(struct ListNode));
		node->val = nums[i];
		node->next = NULL;
		if (!head) {
			head = node;	
			prev = head;
		} else {
			prev->next = node;
			prev = node;
		}
	}
	printf("previous: ");
	show_list(head);
	printf("\r\n");

	reorderList(head);	
	printf("--------------------\r\n");
	printf("After: ");
	show_list(head);
	printf("\r\n");
}

