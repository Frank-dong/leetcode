#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie_tree.h"

typedef struct trie_node {
	int	path;	// 统计使用这个节点的个数
	int	end;	// 是否为有效节点
	void*   data;	// 记录信息
	struct trie_node* next[26];	// 记录下一个字母的信息
}trie_node_t, trie_tree_t;

void* trie_init()
{
	//memcheck_init();
	trie_tree_t* root = calloc(1, sizeof(trie_tree_t));	
	return (void*)root;
}

/**
 * 插入到字典树中
 * 注意：插入的单词只包含带小写字母
 */
void trie_insert(void* root, char* word, void* data)
{
	int	i = 0;
	int	index = 0;
	trie_node_t*	node = (trie_node_t*)root;

	if (!root || !word) {
		return ;
	}

	for (i = 0; i < strlen(word); ++i) {
		index = word[i] - 'a';
		if (index >= 26 || index < 0)
			return;
		if (!node->next[index]) {
			node->next[index] = calloc(1, sizeof(trie_node_t));
		}
		node->next[index]->path++;
		node = node->next[index];
	}
	node->path++;
	node->end = 1;
	node->data = data;

	return ;
}

/**
 * 查找一个单词
 * 返回当前这个节点，需要通过get_node_data()接口来获取其中的数据。
 */
void* trie_search(void* root, char* word)
{
	trie_node_t*	node = (trie_tree_t*)root;
	int	i = 0;
	int	index = 0;

	if (!root || !word)
		return NULL;

	for (i = 0; i < strlen(word) && node; ++i) {
		index = word[i] - 'a';
		if (index > 26 || index < 0)
			return NULL;
		node = node->next[index];
	}
	if (node && node->end == 1) {
		return node;
	}
	return NULL;
}

#define TRACE_LIMIT	30
#define WORD_LEN	3
int trie_get_more(char** rst, 
                int rst_len, 
                trie_node_t* root, 
                int limit, 
                int* got_num,
                char* trace,
                int index,
                char* word)
{
	int	    i = 0;
	int     find_cnt = 0;
	char    word_str[40] = {0};
       
	if (index >= TRACE_LIMIT)
		return 0;

	if (root->end) {
		trace[index] = 0;
		if (strlen(*rst) + strlen(word) + strlen(trace) + 2 >= rst_len) {
			printf("realloc %d\r\n", rst_len*2);
			rst_len *= 2;
			*rst = realloc(*rst, rst_len*2);
		}
        sprintf(*rst, "%s%s%s%s", *rst, (*rst)[0] ? ",":"", word, trace);
        *got_num += 1;
        printf("[%d, limit=%d]rst: %s\r\n", *got_num, limit, *rst);
        if (*got_num >= limit)
            return limit;
	}

	for (i = 0; i < 26; ++i) {
	    // 选择
        trace[index] = 'a' + i;
		//for (int k = 0; k < index; ++k)
			//printf("-");
		//printf("try: %c\r\n", 'a' + i);
        // 判断
		if (root->next[i]) {
			if (trie_get_more(rst, rst_len, root->next[i], limit, got_num, trace, index+1, word) >= limit) { 
				//printf("return limit\r\n");
				return limit;
			}
		} 
    }
    
	return 0;
}

/**
 * 联想查词
 * @word： 输入文本
 * @*num： 查找的最多条目, 同时返回最终查找的数目
 * 
 * return：返回单词列表，以,间隔。例如:about,able,aboard
 * 需要外部释放返回结果
 */
char* trie_get_word_associate(void* root, char* word, int* num)
{
    trie_node_t*	node = (trie_tree_t*)root;
	int	i = 0;
    int index = 0;
	int	got_num = 0;
	char*   rst = NULL;
	char    trace[TRACE_LIMIT] = {0};

	if (!root || !word || !num || *num <= 0)
		return NULL;

    rst = calloc(1, WORD_LEN*(*num));
    for (i = 0; i < strlen(word) && node; ++i) {
		index = word[i] - 'a';
		if (index > 26 || index < 0)
			goto err;
		node = node->next[index];
	}

	if (node)
		trie_get_more(&rst, WORD_LEN*(*num), node, *num, &got_num, trace, 0, word);
	*num = got_num;

	printf("end rst:%s\r\n", rst);
    return rst;
    
 err:
    free(rst);
    return NULL;
}

void* trie_get_node_data(void* node)
{
	trie_node_t*	tmp_node = (trie_node_t*)node;
	return tmp_node->data;
}

static void del_node(trie_tree_t* root, trie_data_free_cb_t free_cb)
{
	int i = 0;

	if (!root)
		return;

	for (i = 0; i < 26; i++) {
		if (root->next[i]) {
			del_node(root->next[i], free_cb);
		}
	}
	if (root->data && free_cb) {
		free_cb(root->data);
	}
	free(root);
}

void trie_deinit(void* root, trie_data_free_cb_t free_cb)
{
	del_node((trie_tree_t*)root, free_cb);
	//memcheck_deinit();
}
