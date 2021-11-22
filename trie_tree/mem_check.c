/********************************************************
 * 通过重定义一个内存申请和释放的接口，来检查代码是否有内存
 * 泄漏
 * ******************************************************/

#include <stdio.h>
#include <stdlib.h>


struct node {
	void*	addr;
	int		len;
	struct node* next;
};

struct node* g_head;

void memcheck_init()
{
	g_head = calloc(1, sizeof(struct node));
	g_head->len = 0;
	g_head->next = NULL;
}

void* my_calloc(int size, int num)
{
	void*	addr = calloc(1, size*num);
	struct node* tmp = NULL;
	struct node* node = calloc(1, sizeof(struct node));	

	node->addr = addr;
	node->len = size*num;
	g_head->len += node->len;

	if (!g_head->next) {
		g_head->next = node;
	} else {
		tmp = g_head->next;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}

	return addr;
}

void my_free(void* addr)
{
	struct node* node = NULL;
	struct node* pre = NULL;

	node = g_head->next;
	pre = g_head;
	while (node && node->addr != addr) {
		pre = node;
		node = node->next;
	}

	if (node) {
		g_head->len -= node->len;
		free(addr);
		pre->next = node->next;
		free(node);
	}
}

void memcheck_show()
{
	struct node* node = NULL;

	node = g_head->next;
	while (node) {
		printf("Addr: 0x%x, len: %d\r\n", (unsigned int)node->addr, node->len);
	}
	printf("******** Total: %d **********\r\n", g_head->len);
}

void memcheck_deinit()
{
	memcheck_show();

	struct node* node = NULL;

	do {
		node = g_head->next;
		free(g_head);
		g_head = node;
	} while (node);
}
