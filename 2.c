

/**
 * 
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
