#include <stdio.h>
#include <stdlib.h>
#include "trie_tree.h"

struct node_t {
	char*	str;
	int		num;
};

struct node_t g_list[] =  {
	{"hello", 1},
	{"hebit", 11},
	{"humain", 11},
	{"helloworld", 2},
	{"helloworldnihaomen", 2},
	{"abondon", 3},
	{"great", 4},
	{"happy", 5},
	{"unbelivaible", 6},
	{"yes", 7},
	{"good", 8},
	{"tonight", 9},
	{"zoo", 10},
};

void free_node(void* data)
{
	struct node_t* node = (struct node_t*)data;
	free(node->str);
}

int main(int argc, char* argv[])
{
	void*	handle = NULL;
	void*	get_node = NULL;
	struct node_t*	node = NULL;
	char*	word_list = NULL;
	int	i = 0;

	handle = trie_init();

	for (i = 0; i < sizeof(g_list)/sizeof(g_list[0]); ++i) {
		node = calloc(1, sizeof(struct node_t));
		node->str = calloc(1, strlen(g_list[i].str) + 1);
		node->num = g_list[i].num;
		strcpy(node->str, g_list[i].str);
		trie_insert(handle, g_list[i].str, (void*)node);
	}

	//get_node = trie_search(handle, argv[1]); 
	//node = (struct node_t*)trie_get_node_data(get_node);
	//printf("word = %s, num = %d\r\n", node->str, node->num);
	int	limit_num = 5;
	word_list = trie_get_word_associate(handle, argv[1], &limit_num);
	printf("Got %d word\r\n", limit_num);
	if (word_list) {
		printf("word list: %s\r\n", word_list);
		free(word_list);
	} else {
		printf("NULL\r\n");
	}


	trie_deinit(handle, free_node);

	return 0;
}
