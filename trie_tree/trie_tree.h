#ifndef __TRIE_TREE_H__
#define __TRIE_TREE_H__

#if 0
struct word_info {
	char*	gb_path;
	char*	us_path;
};
#endif

typedef void (*trie_data_free_cb_t)(void*);

void* trie_init();

/**
 * 插入到字典树中
 * 注意：插入的单词只包含带小写字母
 */
void trie_insert(void* root, char* word, void* data);

/**
 * 查找一个单词
 * 结果需要调用trie_rst_destroy接口进行释放
 */
void* trie_search(void* root, char* word);

/**
 * 获取节点数据
 */
void* trie_get_node_data(void* node);

/**
 * 销毁字典树
 */
void trie_deinit(void* root, trie_data_free_cb_t free_cb);

/**
 * 联想查词
 * @word： 输入文本
 * @num： 查找的最多条目
 * 
 * return：返回单词列表，以,间隔。例如:about,able,aboard
 * 需要外部释放返回结果
 */
char* trie_get_word_associate(void* root, char* word, int* num);


#endif //__TRIE_TREE_H__
